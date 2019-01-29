#include "stdafx.h"
#include "FastFloat3.h"
#ifdef FAST

float3::float3()
{
}

float3::float3(float x, float y, float z) :
	mmv{ _mm_set_ps(0.0f, z, y, x) }
{
}

float3::float3(__m128 val) :
	mmv{ val }
{
}


float3::~float3()
{
}

float3 float3::normalize() const
{
	__m128 dp = _mm_dp_ps(mmv, mmv, 0x7F);
	dp = _mm_sqrt_ps(dp);
	return { _mm_mul_ps(mmv, dp) };
}

#endif