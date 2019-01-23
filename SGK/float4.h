#pragma once
#include <iostream>

class float4
{
public:
	float4();
	float4(float alpha, float red, float green, float blue);
	~float4();

	float& operator[] (const size_t index)
	{
		return arr[index];
	}

	float operator[] (size_t index) const
	{
		return arr[index];
	}

	float4& operator *= (const float num)
	{
		a *= num;
		x *= num;
		y *= num;
		z *= num;

		return *this;
	}

	void clamp(const float min, const float max)
	{
		x = x < min ? min : (x > max ? max : x);
		y = y < min ? min : (y > max ? max : y);
		z = z < min ? min : (z > max ? max : z);
		w = w < min ? min : (w > max ? max : w);
	}

	float4 operator * (const float num)
	{
		return { x * num, y * num, z * num, w * num };
	}

	float4 operator * (float num) const
	{
		return { x * num, y * num, z * num, w * num };
	}

	float4 operator *(const float4 &other)
	{
		return { x * other.x, y * other.y, z * other.z, w * other.w };
	}


	float4 operator + (const float4 &color)
	{
		return float4{ x + color.x, y + color.y, z + color.z, w + color.w };
	}

	float4 operator - (const float4 &color)
	{
		return float4{ x - color.x, y - color.y, z - color.z, w - color.w };
	}

	float4& operator -= (const float value)
	{
		x -= value;
		y -= value;
		z -= value;
		w -= value;

		return *this;
	}

	union
	{
		struct
		{
			float a;
			float r;
			float g;
			float b;
		};

		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		float arr[4];
	};
};
std::ostream& operator<<(std::ostream& out, const float4& vec);

