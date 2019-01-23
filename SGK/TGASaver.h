#pragma once
#include <string>
#include <vector>

class TGASaver
{
public:
	static void saveToFile(const std::string & filename,
		std::vector<uint32_t>* colors, const uint16_t width, const uint16_t heigth);
};

