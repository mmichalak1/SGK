#include "stdafx.h"
#include "PointLight.h"
#include "Math.h"

const float min = -1.f;

float3 Light::ambient = { 0.2f, 0.5f, 0.3f };

PointLight::PointLight(const float3 col, const float3 pos, float intens) :
	Light{ pos, col },
	m_intensity{ intens }
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
	//auto N = vp.vertexToWorld(normal).normalize();
	//auto V = (m_position - vp.vertexToWorld(position * -1.f));
	//auto L = V.normalize();

	//auto R = reflect(L* -1.f, N);

	//auto diff = dot(N, L);
	//diff = diff<0.f ? 0 : diff >1.f ? 1.f : di

	//auto spec = dot((position - vp.eyePos).normalize(), R);
	//spec = spec < 0.f ? 0.f : spec;

	//spec = pow(spec, 64);

	//auto color = ambient + float3{ 1.f, 1.f, 1.f } * diff * m_intensity;
	//color.clampSelf();

	auto pos_cam = vp.toView(-position);
	auto light_cam = vp.world2View(m_position);

	auto normal_cam = vp.toView(normal).normalize();

	auto L = (light_cam - pos_cam).normalize();

	auto diff2 = dot(normal_cam, L);
	diff2 = std::max(0.f, diff2);

	auto R = reflect(L, normal_cam).normalize();
	auto spec = dot(R, pos_cam);
	spec = spec < 0.f ? 0.f : spec > 1.f ? 1.f : spec;
	spec = powf(spec, 40.f);
	//spec = 0.f;

	auto color2 = ambient + m_color
		* diff2 * m_intensity;
	color2.clampSelf();
	return color2;
}

