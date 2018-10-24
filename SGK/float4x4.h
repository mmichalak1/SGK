#pragma once
#include <array>

#include "float4.h"
class float4x4
{
public:
	float4x4();
	~float4x4();

	float4& operator[] (int index) {
		return data.at(index);
	}

private:
	std::array<float4, 4> data;
};

