#include "stdafx.h"
#include "VertexProcessor.h"
#include "Math.h"

#define _USE_MATH_DEFINES
#include <math.h>

constexpr float pidiv = M_PI / 360.f;
constexpr float pidiv180 = M_PI / 180.f;

VertexProcessor::VertexProcessor()
{
	setIdentity();
}

VertexProcessor::~VertexProcessor()
{
}

void VertexProcessor::setPerspective(float fovy, float aspect, float near, float far)
{
	fovy *= pidiv;
	float f = cos(fovy) / sin(fovy);

	view2proj[0] = float4(f / aspect, 0.f, 0.f, 0.f);
	view2proj[1] = float4(0.f, f, 0.f, 0.f);
	view2proj[2] = float4(0.f, 0.f, (far + near) / (near - far), -1.f);
	view2proj[3] = float4(0.f, 0.f, (2.f * far * near) / (near - far), 0.f);
}

void VertexProcessor::setLookAt(const float3 & eye, const float3 & center, const float3 & up)
{
	auto f = center - eye;

	f.normalizeSelf();

	auto s = cross(f, up);
	auto u = cross(s, f);

	world2view[0] = float4(s.x, u.x, -f.x, 0.0f);
	world2view[1] = float4(s.y, u.y, -f.y, 0.0f);
	world2view[2] = float4(s.z, u.z, -f.z, 0.0f);
	world2view[3] = float4(-eye.x, -eye.y, -eye.z, 1.0f);
}

void VertexProcessor::update()
{
	obj2view = mul(world2view, obj2world);
	obj2proj = mul(view2proj, obj2view);
}

float3 VertexProcessor::triangle(const float3 & v) const
{
	auto pos = float4(v.x, v.y, v.z, 1.0f);

	pos = mul(pos, obj2proj);

	return float3{pos.x/pos.w, pos.y/pos.w, pos.z/pos.w};
}

float3 VertexProcessor::vertexToWorld(const float3 & vertex) const
{
	auto pos = float4(vertex.x, vertex.y, vertex.z, 1.0f);

	pos = mul(pos, obj2world);

	return float3{ pos.x / pos.w, pos.y / pos.w, pos.z / pos.w };
}

void VertexProcessor::printData() const
{
	std::cout << "world2View\n";
	std::cout << world2view << std::endl;

	std::cout << "obj2world\n";
	std::cout << obj2world << std::endl;

	std::cout << "view2proj\n";
	std::cout << view2proj << std::endl;

	std::cout << "obj2view\n";
	std::cout << obj2view << std::endl;

	std::cout << "obj2proj\n";
	std::cout << obj2proj << std::endl;
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
	update();
}

void VertexProcessor::multByScale(const float3 &v)
{
	auto m = float4x4{
		{v.x, 0.f, 0.f, 0.f},
	{0.f, v.y, 0.f, 0.f},
	{0.f, 0.f, v.z, 0.f},
	{0.f, 0.f, 0.f, 1.f}};

	obj2world = mul(m, obj2world);
	update();
}

void VertexProcessor::multByRot(const float a, float3 v)
{
	const float s = std::sin(a * pidiv180);
	const float c = std::cos(a * pidiv180);

	///Check optimalization
	const float cmin = 1.f - c;

	///TODO: force normalzied vector
	v.normalizeSelf();
	auto m = float4x4
	{
		{v.x * v.x * cmin + c,       v.x * v.y * cmin - v.z * s, v.x * v.z * cmin + v.y * s, 0.f},
		{v.x * v.y * cmin + v.z * s, v.y * v.y * cmin + c, v.y * v.z * cmin - v.x * s, 0.f},
		{v.x * v.z * cmin - v.y * s, v.y * v.z * cmin + v.x * s, v.z * v.z * cmin + c, 0.f},
		{0.f, 0.f, 0.f, 1.f}
	};

	obj2world = mul(m, obj2world);
	update();
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