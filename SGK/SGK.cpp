// SGK.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "ImageBuffer.h"
#include "TGASaver.h"

#include <chrono>
#include <iostream>

int main()
{
	auto timerStart = std::chrono::high_resolution_clock::now();

	auto imageBuffer = ImageBuffer(800, 600);

	uint32_t clearColor = 0x00000000;
	/*imageBuffer.clearWithColor(clearColor);
	TGASaver::saveToFile("lama2", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());
*/
	clearColor = 0x00000000;
	imageBuffer.clearWithColor(clearColor);
	float4 triangleColor{ 0.0f, 1.0f, 0.0f, 0.0f };
	//imageBuffer.rasterize(
	//	{ 1.0f,  1.0f, 0.0f },
	//	{ 0.8f,  0.8f, 0.0f },
	//	{ -0.5f, 0.0f, 0.0f },
	//	triangleColor,
	//	triangleColor,
	//	triangleColor);

	triangleColor = { 0.0f, 1.0f, 0.0f, 0.0f };
	imageBuffer.rasterize(
		{ -0.8f, -0.8f, 0.0f },
		{  0.4f,  0.0f, 0.0f },
		{ -0.8f,  0.6f, 0.0f },
		triangleColor,
		triangleColor,
		triangleColor);

	auto timerEnd = std::chrono::high_resolution_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::duration<double>>(timerEnd - timerStart);

	std::cout << "Rendered in: " << time.count();


	TGASaver::saveToFile("lamared", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());


	std::cin.get();
	return 0;
}

