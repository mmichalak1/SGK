#include "stdafx.h"
#include "TGASaver.h"
#include <fstream>
#include <assert.h>
#include <iostream>


const std::string tgaExt = ".tga";
const std::string ppmExt = ".ppm";

unsigned short header[9] = {
	0x0000, 0x0002, 0x0000, 0x0100, 0x0, 0x0,
	0x0100, 0x0100,
	0x0820
};

void TGASaver::saveToFile(const std::string & filename, std::vector<uint32_t>* colors, const uint16_t width, const uint16_t heigth)
{
	auto fileExt = filename + tgaExt;

	FILE* file;

	fopen_s(&file, fileExt.c_str(), "wb+");

	header[6] = width;
	header[7] = heigth;

	fwrite(header, 2, 9, file);
	fwrite(colors->data(), sizeof(uint32_t), colors->size(), file);

	fclose(file);
}

void TGASaver::toPPM(const std::string & filename, std::vector<Color>* colors, const uint16_t width, const uint16_t heigth)
{
	auto fileExt = filename + ppmExt;

	//std::reverse(colors->begin(), colors->end());

	auto stream = std::ofstream(fileExt, std::ios::out | std::ios::binary);
	stream << "P6\n" << width << " " << heigth << "\n255\n";
	for (const auto& color : *colors)
		stream << color.R << color.G << color.B;
	stream.close();
}
