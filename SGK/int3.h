#pragma once
class int3
{
public:

	union
	{
		struct
		{
			int x;
			int y;
			int z;
		};

		int arr[3];
	};
	int& operator[] (size_t index){
		return arr[index];
	}

	int3();
	int3(int x, int y, int z);
	~int3();
};

