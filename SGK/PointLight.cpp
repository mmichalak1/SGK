#include "stdafx.h"
#include "PointLight.h"
#include "Math.h"

const float min = -1.f;

float3 Light::ambient = { 0.3f, 0.3f, 0.3f};

PointLight::PointLight(const float3 col, const float3 pos, float intens, int specPow) :
	Light{ pos, col, intens, specPow }
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
	auto L = m_position - V;
	L.normalizeSelf();

	auto diff = dot(L, N);
	diff = std::max(0.f, diff);

	auto spec = 0.f;
	if (diff > 0.000f)
	{
		auto R = reflect(L, N).normalize();

		spec = dot(R, V);
		spec = std::pow(spec, m_specPow);
		spec = std::max(0.f, spec);;
	}
	auto color = Light::ambient + m_color * m_intensity * diff;
	color += m_color * m_intensity * spec;
	color.clampSelf();
	return color;
}

float3 PointLight::calculateLightNoClamps(const float3 position, const float3 & normal, const VertexProcessor & vp) const
{
	auto N = vp.light(normal).normalize(); //obj2View (3x3)

	auto V = vp.toView(position); //obj2view
	auto L = vp.world2View(m_position) - V; //world2View
	L.normalizeSelf();

	auto diff = dot(L, N);
	diff = std::max(0.f, diff);

	auto spec = 0.f;
	if (diff > 0.000f)
	{
		auto R = reflect(L, N).normalize();

		spec = dot(R, V.normalize());
		spec = std::max(0.f, spec);
		spec = std::pow(spec, m_specPow);

	}
	auto color = m_color * m_intensity * diff;
	color += float3{ 1.0f, 1.0f, 1.0f } *m_intensity * spec;
	color.clampSelf();
	return color;
}

