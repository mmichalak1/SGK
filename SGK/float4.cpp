#include "stdafx.h"
#include "float4.h"


float4::float4()
{
}

float4::float4(float alpha, float red, float green, float blue) :
	a{alpha},
	x{red},
	y{green},
	z{blue}
{
}


float4::~float4()
{
}
