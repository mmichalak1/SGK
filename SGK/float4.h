#pragma once
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

	float4& operator *= (const float num)
	{
		a *= num;
		x *= num;
		y *= num;
		z *= num;

		return *this;
	}

	float4 operator * (const float num)
	{
		return float4{ a * num, x * num, y * num, z * num };
	}

	float4 operator + (const float4 &color)
	{
		return float4{ a + color.a, x + color.x, y + color.y, z + color.z };
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
			float a;
			float x;
			float y;
			float z;
		};

		float arr[4];
	};
};

