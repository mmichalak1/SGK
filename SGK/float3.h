#pragma once

#include <cmath>
#include <iostream>

struct float3
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float arr[3];
	};

	float operator[] (int index) const
	{
		return arr[index];
	}

	float3& operator += (const float3 &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	void normalizeSelf();

	float3();
	float3(float x, float y, float z);
	~float3();
};
std::ostream& operator<<(std::ostream& out, const float3& vec);
float3 operator - (const float3 &v1, const float3 &v2);


