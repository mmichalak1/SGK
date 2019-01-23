#include "stdafx.h"
#include "float4.h"


float4::float4()
{
}

float4::float4(float alpha, float red, float green, float blue) :
	a{alpha},
	r{red},
	g{green},
	b{blue}
{
}


float4::~float4()
{
}

std::ostream & operator<<(std::ostream & out, const float4 & vec)
{
	out << "< " << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << " >";
	return out;
}
