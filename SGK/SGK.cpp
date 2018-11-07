// SGK.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "ImageBuffer.h"
#include "TGASaver.h"

#include <chrono>
#include <iostream>

using Clock = std::chrono::high_resolution_clock;
using duration = std::chrono::duration<double>;

int main()
{
	auto timerStart = Clock::now();
	auto imageBuffer = ImageBuffer(800, 600);

	uint32_t clearColor = uint32_t{ 0x00000000 };
	imageBuffer.clearWithColor(clearColor);

	imageBuffer.rasterize(
		{ -0.5f, 0.0f, 1.2f },
		{ 0.8f,  0.8f, 0.2f },
		{ 1.0f,  1.0f, 0.2f });

	imageBuffer.rasterize(
		{ -0.8f, -0.8f, 1.0f },
		{  0.4f,  0.0f, 1.0f },
		{ -0.8f,  0.6f, 1.0f });

	auto timerEnd = Clock::now();
	auto time = std::chrono::duration_cast<duration>(timerEnd - timerStart);

	std::cout << "Rendered in: " << time.count();
	TGASaver::saveToFile("lamared", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());

	std::cin.get();
	return 0;
}

