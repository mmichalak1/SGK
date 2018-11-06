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
			float z;
			float x;
			float y;
			float z;
		};

		float arr[4];
	};
};

