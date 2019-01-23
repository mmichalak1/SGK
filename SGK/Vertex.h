#pragma once
#include "float3.h"
#include "float4.h"

class Vertex
{
public:
	Vertex(float3 pos, float3 normal);
	~Vertex();


	float3 position;
	float3 normal;
};

