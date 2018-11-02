// SGK.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "ImageBuffer.h"
#include "TGASaver.h"

int main()
{
	auto imageBuffer = ImageBuffer(800, 600);

	uint32_t clearColor = 0x000000ff;
	/*imageBuffer.clearWithColor(clearColor);
	TGASaver::saveToFile("lama2", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());
*/
	clearColor = 0x00ffffff;
	imageBuffer.clearWithColor(clearColor);
	float4 triangleColor{ 0.0f, 1.0f, 0.0f, 0.0f };
	imageBuffer.rasterize(
		{ 0.0f,  0.8f, 0.0f },
		{ 0.8f,  0.8f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		triangleColor);

	triangleColor = { 0.0f, 1.0f, 0.0f, 0.0f };
	imageBuffer.rasterize(
		{ -0.9f, -0.9f, 0.0f },
		{  0.6f, -0.9f, 0.0f },
		{  0.6f,  0.9f, 0.0f },
		triangleColor);

	TGASaver::saveToFile("lamared", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());

	return 0;
}

