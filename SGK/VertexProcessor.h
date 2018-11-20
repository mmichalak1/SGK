#pragma once
#include "float4x4.h"
#include "float3.h"

class VertexProcessor
{
public:
	VertexProcessor();
	~VertexProcessor();

	void setPerspective(float fovy, float aspect, float near, float far);
	void setLookAt(const float3 &center, const float3 &eye, const float3 &up = float3{ 0.f, 1.f, 0.f });

	void triangle(const float3 &v1, const float3 &v2, const float3 &v3, const float3 &scale, const float3 &rotation);
private:

	void multByTransl(const float3 &v);
	void multByScale(const float3 & v);

	void multByRot(const float a, float3 & v);

	void setIdentity();

	float4x4 obj2world;
	float4x4 world2view;
	float4x4 view2proj;
};

