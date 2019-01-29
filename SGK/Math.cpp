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
	return float3{
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x };
}

float dot(const float3 & v1, const float3 & v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float dot(const float4 & v1, const float4 & v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;

}

float4x4 mul(const float4x4 & m1, const float4x4 & m2)
{
	float4x4 result;

	auto trs = transpose(m1);

	return {
		{dot(trs[0], m2[0]), dot(trs[1], m2[0]),dot(trs[2], m2[0]),dot(trs[3], m2[0])},
		{dot(trs[0], m2[1]), dot(trs[1], m2[1]),dot(trs[2], m2[1]),dot(trs[3], m2[1])},
		{dot(trs[0], m2[2]), dot(trs[1], m2[2]),dot(trs[2], m2[2]),dot(trs[3], m2[2])},
		{dot(trs[0], m2[3]), dot(trs[1], m2[3]),dot(trs[2], m2[3]),dot(trs[3], m2[3])}
	};
}

float4x4 transpose(const float4x4 &mat)
{
	auto r1 = float4{ mat[0].x,mat[1].x, mat[2].x, mat[3].x };
	auto r2 = float4{ mat[0].y,mat[1].y, mat[2].y, mat[3].y };
	auto r3 = float4{ mat[0].z,mat[1].z, mat[2].z, mat[3].z };
	auto r4 = float4{ mat[0].w,mat[1].w, mat[2].w, mat[3].w };

	return float4x4{ r1, r2, r3, r4 };
}

float4 mul(const float4& vec, const float4x4& mat)
{
	auto trns = transpose(mat);

	return float4{
		dot(vec, trns[0]),
		dot(vec, trns[1]),
		dot(vec, trns[2]),
		dot(vec, trns[3]) };
}

float4 mix(const float4 & c1, const float4 & c2, float ratio)
{
	return c1 * (1.f - ratio) + c2 * ratio;
}

float3 reflect(const float3& L, const float3& N)
{
	const auto Nn = N.normalize();
	return N * 2.f * dot(N, L) - L;
}
