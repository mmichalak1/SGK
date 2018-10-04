#include "stdafx.h"
#include "TGASaver.h"
#include <fstream>
#include <assert.h>
#include<iostream>


const std::string ext = ".tga";

#pragma pack(4)
struct TGAHeader
{
	uint8_t id = 0;
	uint8_t	color = 0;
	uint8_t type = 2;
	uint16_t index = 0;
	uint16_t count = 0;
	uint8_t colorWidth = 0;
	uint16_t xCoord = 0;
	uint16_t yCoord = 0;
	uint16_t width = 256;
	uint16_t heigth = 256;
	uint8_t pixWidth = 32;
	uint8_t flags = 0;
};


void TGASaver::saveToFile(const std::string & filename, std::vector<uint32_t>* colors, const uint16_t width, const uint16_t heigth)
{
	auto fileExt = filename + ext;

	#pragma warning(disable : 4996)
	FILE *file = fopen(fileExt.c_str(), "wb");

	auto header = TGAHeader();
	header.width = width;
	header.heigth = heigth;
	header.flags = 236;

	struct TGAHeader _UNALIGNED *n = &header;

	fwrite(&n->id, 1, 1, file);
	fwrite(&n->color, 1, 1, file);
	fwrite(&n->type, 1, 1, file);
	fwrite(&n->index, 2, 1, file);
	fwrite(&n->count, 2, 1, file);
	fwrite(&n->colorWidth, 1, 1, file);
	fwrite(&n->xCoord, 2, 1, file);
	fwrite(&n->yCoord, 2, 1, file);
	fwrite(&n->width, 2, 1, file);
	fwrite(&n->heigth, 2, 1, file);
	fwrite(&n->pixWidth, 1, 1, file);
	fwrite(&n->flags, 1, 1, file);

	uint32_t cool = 0x00ff0000;

	std::cout << "Size of struct: " << sizeof(header);

	fwrite(colors->data(), sizeof(uint32_t) , colors->size(), file);

	fclose(file);
}
