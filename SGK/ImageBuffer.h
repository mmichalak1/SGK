#pragma once
#include <vector>

#include "float3.h"
#include "float4.h"

class ImageBuffer
{
public:
	ImageBuffer(uint16_t width, uint16_t height);
	~ImageBuffer();

	void clearWithColor(const uint32_t &color);

	void rasterize(const float3 &t1, const float3 &t2, const float3 &t3,
		float4 color = float4( 0.0f, 1.0f, 0.0f, 0.0f ), float4 t2Color = { 0.0f, 0.0f, 1.0f, 0.0f }, float4 t3Color = { 0.0f, 0.0f, 0.0f, 1.0f });

	std::vector<uint32_t>* getColors();
	uint16_t getWidth() const;
	uint16_t getHeigth() const;

private:
	std::vector<float> depths;
	std::vector<uint32_t> colors;

	uint16_t m_width;
	uint16_t m_height;

	uint32_t toUintColor(const float4 &color) const;
};

