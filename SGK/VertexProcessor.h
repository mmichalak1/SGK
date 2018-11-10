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

private:

	void multByTransl(const float3 &v);

	float4x4 obj2world;
	float4x4 world2view;
	float4x4 view2proj;
};

