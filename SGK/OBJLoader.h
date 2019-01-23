#pragma once
#include "Mesh.h"

class OBJLoader
{
public:
	static Mesh loadFromFile(const std::string& filename);

	OBJLoader();
	~OBJLoader();

private:
	static float3 loadFloat3(const std::string& line);
	static void loadIndices();
};

