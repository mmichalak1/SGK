#pragma once
#include "float3.h"
#include "float4.h"
#include "float4x4.h"

float3 normalize(const float3 &vector);
float3 cross(const float3 &v1, const float3 &v2);
float3 dot(const float3 &v1, const float3 &v2);
float4 dot(const float4 &v1, const float4 &v2);

float4x4 mul(const float4x4 &m1, const float4x4 &m2);




