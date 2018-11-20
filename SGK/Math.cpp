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

	auto m1c1 = m1[0];
	auto m1c2 = m1[1];
	auto m1c3 = m1[2];
	auto m1c4 = m1[3];

	auto m2c1 = m2[0];
	auto m2c2 = m2[1];
	auto m2c3 = m2[2];
	auto m2c4 = m2[3];

	result[0] = m1c1 * m2c1[0] + m1c2 * m2c1[1] + m1c3 * m2c1[2] + m1c4 * m2c1[3];
	result[1] = m1c1 * m2c2[0] + m1c2 * m2c2[1] + m1c3 * m2c2[2] + m1c4 * m2c2[3];
	result[2] = m1c1 * m2c3[0] + m1c2 * m2c3[1] + m1c3 * m2c3[2] + m1c4 * m2c3[3];
	result[3] = m1c1 * m2c4[0] + m1c2 * m2c4[1] + m1c3 * m2c4[2] + m1c4 * m2c4[3];

	return result;
}
