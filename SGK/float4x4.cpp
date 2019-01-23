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
	return data[index];
}

std::ostream & operator<<(std::ostream & out, const float4x4 & vec)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			std::cout << vec[j][i] << " ";
		}
		std::cout << std::endl;
	}
	return out;
}
