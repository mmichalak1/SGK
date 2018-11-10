#include "stdafx.h"
#include "float3.h"


void float3::normalizeSelf()
{
	float len = std::sqrt(x * x + y * y + z * z);
	if (len > 0.0001f)
	{
		x /= len;
		y /= len;
		z /= len;
	}
	else
		x = y = z = 0.f;
}

float3::float3()
{
}

float3::float3(float x, float y, float z) : 
	x{x},
	y{y},
	z{z}
{
}


float3::~float3()
{
}

std::ostream & operator<<(std::ostream & out, const float3 & vec)
{
	out << "< " << vec.x << " " << vec.y << " " << vec.z << " >";
	return out;
}

float3 operator-(const float3 & v1, const float3 & v2)
{
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}
