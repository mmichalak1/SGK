#include "stdafx.h"
#include "Math.h"

float3 normalize(const float3 & vector)
{
	float len = std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	if (len > 0.0001f)
		return float3{ vector.x / len, vector.y / len, vector.z / len };
	else
		return float3{ 0.f, 0.f, 0.f };
}

float3 cross(const float3 & v1, const float3 & v2)
{
	return float3{ v1.y * v1.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}

float3 dot(const float3 & v1, const float3 & v2)
{
	return float3{ v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
}

float4 dot(const float4 & v1, const float4 & v2)
{
	return float4{v1.a * v2.a, v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };

}

float4x4 mul(const float4x4 & m1, const float4x4 & m2)
{
	float4x4 result;
	
}
