#pragma once
#include "float4.h"
#include "float3.h"
class PointLight
{
public:
	PointLight(const float4 color, const float3 postion, const float intensity);
	~PointLight();

	float4 color;
	float3 position;

	float intensity;
};

