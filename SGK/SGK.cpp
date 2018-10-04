// SGK.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "ImageBuffer.h"
#include "TGASaver.h"

int main()
{
	auto imageBuffer = ImageBuffer(800, 600);

	uint32_t clearColor = 0x000000ff;
	imageBuffer.clearWithColor(clearColor);

	TGASaver::saveToFile("lama2", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());

	getchar();

    return 0;
}

