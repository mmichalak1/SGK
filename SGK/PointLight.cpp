#include "stdafx.h"
#include "PointLight.h"
#include "Math.h"

const float min = -1.f;

float3 Light::ambient = { 0.2f, 0.5f, 0.3f };

PointLight::PointLight(const float4 col, const float3 pos, float intens) :
	Light{ pos, col },
	m_intensity{ intens }
{
}


PointLight::~PointLight()
{
}

float4 PointLight::calculateLight(const float3 position, const float3& normal) const
{
	auto toLight = m_position - position;
	toLight.normalizeSelf();
	auto angle = dot(normal, toLight);

	angle = std::max(angle, 0.f);

	auto result = m_color * angle * m_intensity;
	float4 color = float4{ 1.f, 1.f, 1.f, 1.f };

	result = color - result;

	result.clamp(0.f, 1.0f);
	return result;
}

float3 PointLight::calculateLight(const float3 position, const float3 & normal, const VertexProcessor & vp) const
{
	auto N = vp.vertexToWorld(normal.normalize()).normalize();
	auto V = (m_position - vp.vertexToWorld(position));
	auto L = V.normalize();

	auto R = reflect(L* -1.f, N);

	auto diff = dot(N, L);
	diff = diff<0.f ? 0 : diff >1.f ? 1.f : diff;

	//auto spec = dot((position - vp.eyePos).normalize(), R);
	//spec = spec < 0.f ? 0.f : spec;

	//spec = pow(spec, 64);

	auto color = ambient + float3{ 1.f, 1.f, 1.f } * diff;
	color.clampSelf();

	auto pos_cam = vp.toView(position);
	auto light_cam = vp.world2View(m_position);
	auto normal_cam = vp.toView(normal.normalize()).normalize();

	auto diff2 = dot(normal_cam, (light_cam - pos_cam).normalize());
	diff2 = std::max(0.f, diff2);

	auto color2 = ambient + float3{ 1.f, 1.f, 1.f } * diff2;
	color2.clampSelf();
	return color2;
}

