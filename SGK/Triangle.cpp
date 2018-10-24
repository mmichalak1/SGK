#include "stdafx.h"
#include "Triangle.h"


Triangle::Triangle() :
	v1{ 0.0, 0.0, 0.0 },
	v2{ 0.0, 0.0, 0.0 },
	v3{ 0.0, 0.0, 0.0 }

{
}

Triangle::Triangle(float3 inv1, float3 inv2, float3 inv3) :
	v1{ inv1 },
	v2{ inv2 },
	v3{ inv3 }
{

}


Triangle::~Triangle()
{
}
