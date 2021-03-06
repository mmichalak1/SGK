#pragma once
#include "Light.h"
#include "float4.h"

class PointLight : public Light
{
public:
	PointLight(const float3 color, const float3 postion, const float intensity, const int specPow);
	~PointLight();

	float3 calculateLight(const float3 position, const float3& normal) const override;
	float3 calculateLight(const float3 position, const float3& normal, const VertexProcessor& vp) const override;
	float3 calculateLightNoClamps(const float3 position, const float3& norma, const VertexProcessor& vp) const override;

};

