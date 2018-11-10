#pragma once
#include <array>

#include "float4.h"
class float4x4
{
public:
	float4x4();
	~float4x4();

	float4x4(const float4 v1, const float4 v2, const float4 v3, const float4 v4);

	float4& operator[] (int index) {
		return data.at(index);
	}

private:
	std::array<float4, 4> data;
};

