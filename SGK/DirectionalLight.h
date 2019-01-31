#pragma once
#include "Light.h"
class DirectionalLight :
	public Light
{
public:
	DirectionalLight(const float3& color, const float3& dir, float intensity);

	float3 calculateLight(const float3 position, const float3 & normal) const override { return float3{ 0.f,0.f,0.f }; }
	float3 calculateLight(const float3 position, const float3 & normal, const VertexProcessor & vp) const override;
	virtual ~DirectionalLight();
};

