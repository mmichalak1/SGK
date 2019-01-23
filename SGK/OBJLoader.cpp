#include "stdafx.h"
#include "OBJLoader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

Mesh OBJLoader::loadFromFile(const std::string& filename)
{
	auto result = Mesh();

	auto fileStream = std::ifstream(filename);

	std::string line;

	auto points = std::vector<float3>();
	auto normals = std::vector<float3>();
	auto texturing = std::vector<float3>();

	while (std::getline(fileStream, line))
	{
		if (line == "")
			continue;

		if (line.rfind("v ", 0) == 0)
		{
			points.push_back(loadFloat3(line));
		}
		else if (line.rfind("vn", 0) == 0)
		{
			normals.push_back(loadFloat3(line));
		}
		else if (line.rfind("vt", 0) == 0)
		{
			texturing.push_back(loadFloat3(line));
		}
		else if (line.rfind("g" , 0) == 0)
		{
			auto mesh = Mesh();

			while (std::getline(fileStream, line))
			{
				if (line.rfind("f ", 0) == 0)
				{
					points.push_back(loadFloat3(line));
				}
			}
		}

	}

	return result;
}

OBJLoader::OBJLoader()
{
}


OBJLoader::~OBJLoader()
{
}

float3 OBJLoader::loadFloat3(const std::string & line)
{
	auto ss = std::istringstream(line);

	auto result = std::vector<std::string>(std::istream_iterator<std::string>{ss},
		std::istream_iterator<std::string>());

	return {std::stof(result[1]), std::stof(result[2]), std::stof(result[3])};
}

void OBJLoader::loadIndices()
{

}
