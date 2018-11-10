#include "stdafx.h"
#include "VertexProcessor.h"
#include "Math.h"

#define _USE_MATH_DEFINES
#include <math.h>

constexpr float pidiv = M_PI / 360.f;

VertexProcessor::VertexProcessor()
{
	


VertexProcessor::~VertexProcessor()
{
}

void VertexProcessor::setPerspective(float fovy, float aspect, float far, float near)
{
	fovy *= pidiv;
	float f = cos(fovy) / sin(fovy);

	view2proj[0] = float4(f / aspect, 0.f, 0.f, 0.f);
	view2proj[1] = float4(0.f, f, 0.f, 0.f);
	view2proj[2] = float4(0.f, 0.f, (far + near) / (near - far), -1.f);
	view2proj[3] = float4(0.f, 0.f, (2.f * far * near) / (near - far), 0.f);
}

void VertexProcessor::setLookAt(const float3 & center, const float3 & eye, const float3 & up)
{
	auto f = center - eye;
	f.normalizeSelf();
	
	auto s = cross(f, up);
	auto u = cross(s, f);

	world2view[0] = float4(s[0], u[0], -f[0], 0);
	world2view[1] = float4(s[1], u[1], -f[1], 0);
	world2view[2] = float4(s[2], u[2], -f[2], 0);
	world2view[3] = float4(-eye.x, -eye.y, -eye.z, 1);
}

void VertexProcessor::multByTransl(const float3 & v)
{
	auto m = float4x4{
		float4{1.f, 0, 0, 0},
		float4{0.f, 1.f, 0, 0},
		float4{0.f, 0, 1.f, 0},
		float4{v.x, v.y, v.z, 1.f}
	};

	obj2world = mul(m, obj2world);
}
