#pragma once
#include "float4x4.h"
#ifdef FAST
#include "FastFloat3.h"
#else // FAST
#include "float3.h"
#endif

class VertexProcessor
{
public:
	VertexProcessor();
	~VertexProcessor();

	void multByTransl(const float3 &v);
	void multByScale(const float3 & v);

	void multByRot(const float a, float3 v);

	void fastMulByRot(const float a, float3 v);

	void setPerspective(float fovy, float aspect, float near, float far);
	void setLookAt(const float3 &eye, const float3 &center, const float3 &up = float3{ 0.f, 1.f, 0.f });

	void update();

	float3 triangle(const float3 &v1) const;
	float3 vertexToWorld(const float3& vertex) const;
	float3 toView(const float3& vec) const;
	float3 world2View(const float3 vec) const;

	void printData() const;

	float3 lookDir;
	float3 eyePos;
private:

	void setIdentity();

	float4x4 obj2world;
	float4x4 world2view;
	float4x4 view2proj;

	float4x4 obj2view;
	float4x4 obj2proj;
};

