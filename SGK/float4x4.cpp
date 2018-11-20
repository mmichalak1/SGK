#include "stdafx.h"
#include "float4x4.h"


float4x4::float4x4()
{
}


float4x4::~float4x4()
{
}


float4x4::float4x4(const float4 v1, const float4 v2, const float4 v3, const float4 v4)
{
	data[0] = v1;
	data[1] = v2;
	data[2] = v3;
	data[3] = v4;
}

float4& float4x4::operator[](const int i)
{
	return data[i];
}

const float4 float4x4::operator[](const int index) const
{
	return data.at(index);
}
