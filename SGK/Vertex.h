#pragma once
#ifdef FAST
#include "FastFloat3.h"
#else // FAST
#include "float3.h"
#endif

#include "float4.h"

class Vertex
{
public:
	Vertex(float3 pos, float3 normal);
	~Vertex();


	float3 position;
	float3 normal;
};

