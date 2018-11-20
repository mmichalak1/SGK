#include "stdafx.h"
#include "VertexProcessor.h"
#include "Math.h"

#define _USE_MATH_DEFINES
#include <math.h>

constexpr float pidiv = M_PI / 360.f;
constexpr float pidiv180 = M_PI / 180.f;

VertexProcessor::VertexProcessor()
{
}

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

void VertexProcessor::triangle(const float3 & v1, const float3 & v2, const float3 & v3, const float3 & scale, const float3 & rotation)
{
	setIdentity();

	

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

void VertexProcessor::multByScale(const float3 &v)
{
	auto m = float4x4{
		{v.x, 0.f, 0.f, 0.f},
	{0.f, v.y, 0.f, 0.f},
	{0.f, 0.f, v.z, 0.f},
	{0.f, 0.f, 0.f, 1.f}};

	obj2world = mul(m, obj2world);
}

void VertexProcessor::multByRot(const float a, float3 &v)
{
	float s = std::sin(a * pidiv180);
	float c = std::cos(a * pidiv180);


	///Check optimalization
	float cmin = 1.f - c;

	///TODO: force normalzied vector
	v.normalizeSelf();
	auto m = float4x4
	{
		{v.x * v.x * cmin + c, v.x * v.y * cmin - v.z * s, v.x * v.z * cmin + v.y * s, 0.f},
		{v.x * v.y * cmin + v.z * s, v.y * v.y * cmin + c, v.y * y.z * cmin - v.x * s, 0.f},
		{v.x * v.z * cmin - v.y * s, v.y * v.z * cmin + v.x * s, v.z * v.z * cmin + c, 0.f},
		{0.f, 0.f, 0.f, 1.f} 
	};

	obj2world = mul(m, obj2world);
}

void VertexProcessor::setIdentity()
{
	obj2world = float4x4{
		{1.f, 0.f, 0.f, 0.f},
		{0.f, 1.f, 0.f, 0.f},
		{0.f, 0.f, 1.f, 0.f},
		{0.f, 0.f, 0.f, 1.f}
	};
}