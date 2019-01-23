#include "stdafx.h"
#include "Vertex.h"


Vertex::Vertex(float3 pos, float3 norm) :
	position{pos},
	normal{ norm }
{
}


Vertex::~Vertex()
{
}
