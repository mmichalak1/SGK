#pragma once
#ifdef FAST
#include "FastFloat3.h"
#else // FAST
#include "float3.h"
#endif

#include "float4.h"
#include "float4x4.h"

float3 normalize(const float3 &vector);
float3 cross(const float3 &v1, const float3 &v2);
float dot(const float3 &v1, const float3 &v2) ;
float dot(const float4 &v1, const float4 &v2);

float4x4 mul(const float4x4 &m1, const float4x4 &m2);
float4 mul(const float4& vec, const float4x4& mat);
float4 fastMul(const float4& vec, const float4x4& mat);

float4 mix(const float4& c1, const float4& c2, float ratio);

float4x4 transpose(const float4x4 &mat);
float3 reflect(const float3& v1, const float3& v2);




