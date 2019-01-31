#include "stdafx.h"
#include "PointLight.h"
#include "Math.h"

const float min = -1.f;

float3 Light::ambient = { 0.3f, 0.3f, 0.3f};

PointLight::PointLight(const float3 col, const float3 pos, float intens) :
	Light{ pos, col, intens }
{
}


PointLight::~PointLight()
{
}

float3 PointLight::calculateLight(const float3 position, const float3& normal) const
{
	auto N = normal.normalize();
	auto V = (m_position - position);
	auto L = V.normalize();

	auto diff = dot(N, L);
	diff = diff<0.f ? 0 : diff >1.f ? 1.f : diff;

	auto result = ambient + m_color * diff;

	result.clampSelf();
	return result;
}

float3 PointLight::calculateLight(const float3 position, const float3 & normal, const VertexProcessor & vp) const
{
	auto N = vp.light(normal).normalize();

	auto V = vp.toView(position).normalize();
	auto L = m_position.normalize() - V;
	L.normalizeSelf();

	auto diff = dot(L, N);
	diff = std::max(0.f, diff);

	auto spec = 0.f;
	if (diff > 0.000f)
	{
		auto R = reflect(L, N).normalize();

		spec = dot(R, V);
		spec = std::pow(spec, 6);
		spec = std::max(0.f, spec);;
	}
	auto color = Light::ambient + m_color * m_intensity * diff;
	color += m_color * m_intensity * spec;
	color.clampSelf();
	return color;
}

