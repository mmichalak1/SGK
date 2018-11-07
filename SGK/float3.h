#pragma once
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
	};

	float3();
	float3(float x, float y, float z);
	~float3();
};



