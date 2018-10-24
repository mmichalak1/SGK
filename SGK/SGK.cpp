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

	imageBuffer.triangle(
		{ 0.0F, 0.0F, 0.0F },
		{ 0.0F, 0.0F, 0.0F },
		{ 0.0F, 0.0F, 0.0F },
		{ 0.0F, 0.0F, 0.0F, 1.0F });

	TGASaver::saveToFile("lamared", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());

	return 0;
}

