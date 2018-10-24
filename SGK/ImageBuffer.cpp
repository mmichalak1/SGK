#include "stdafx.h"
#include "ImageBuffer.h"

union colorU
{
	uint32_t uint32;
	uint8_t colors[4];
};


ImageBuffer::ImageBuffer(uint16_t width, uint16_t height) :
	m_height{height},
	m_width{width}
{
	colors.clear();
	depths.resize(width * height);
	colors.resize(width * height);
}


ImageBuffer::~ImageBuffer()
{
}

void ImageBuffer::clearWithColor(const uint32_t & color)
{
	for (auto &pixColor : colors)
		pixColor = color;
}

void ImageBuffer::triangle(const float3 &t1, const float3 &t2, const float3 &t3, const float4 &color)
{
	auto uintColor = toUintColor(color);
	clearWithColor(uintColor);
}

std::vector<uint32_t>* ImageBuffer::getColors()
{
	return &colors;
}

uint16_t ImageBuffer::getWidth() const
{
	return m_width;
}

uint16_t ImageBuffer::getHeigth() const
{
	return m_height;
}

uint32_t ImageBuffer::toUintColor(const float4 & color) const
{
	colorU c;
	c.colors[0] = color.a * 255;
	c.colors[1] = color.x * 255;
	c.colors[2] = color.y * 255;
	c.colors[3] = color.z * 255;

	return c.uint32;
}
