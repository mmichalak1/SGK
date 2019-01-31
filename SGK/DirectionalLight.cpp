#include "stdafx.h"
#include "DirectionalLight.h"
#include "Math.h"

DirectionalLight::DirectionalLight(const float3 & color, const float3 & dir, float intensity) :
	Light{ dir.normalize(), color, intensity }
{
}

float3 DirectionalLight::calculateLight(const float3 position, const float3 & normal, const VertexProcessor & vp) const
{
	auto L = vp.light(m_position).normalize();
	auto N = vp.light(normal).normalize();

	auto diff = dot(L, N);
	diff = std::max(0.f, diff);

	auto spec = 0.f;
	if (diff > 0.0001f)
	{
		auto V = vp.toView(position).normalize();
		auto R = reflect(L, N).normalize();

		spec = dot(R, V);
		spec = std::pow(spec, 60);
		spec = std::max(0.f, spec);
	}


	auto color = Light::ambient + m_color * m_intensity * diff + m_color * m_intensity * spec;
	color.clampSelf();

	return color;
}

DirectionalLight::~DirectionalLight()
{
}
