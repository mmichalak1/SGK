#pragma once
#include "float3.h"

class Triangle
{
public:
	Triangle();
	Triangle(float3 inv1, float3 inv2, float3 inv3);
	~Triangle();
private:

	float3 v1;
	float3 v2;
	float3 v3;
};

