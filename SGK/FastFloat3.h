#pragma once
#include "stdafx.h"
#ifdef  FAST
#include <cmath>
#include <iostream>
#include <intrin.h>

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
		__m128 mmv;
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

	inline float3 operator *(const float number) const
	{
		return{ x* number, y * number, z*number };
	}


	inline float3 operator +(const float3& other)
	{
		return { _mm_add_ps(mmv, other.mmv) };
	}

	inline float3 operator *(const float3& other) const
	{
		return { x * other.x, y * other.y, z * other.z };
	}

	void normalizeSelf();
	void clampSelf(const float min = 1.f, const float max = 1.f);

	float3 normalize() const;

	float3();
	float3(float x, float y, float z);
	float3(__m128 val);
	~float3();
};
std::ostream& operator<<(std::ostream& out, const float3& vec);
float3 operator - (const float3 &v1, const float3 &v2);

#endif //  FAST

