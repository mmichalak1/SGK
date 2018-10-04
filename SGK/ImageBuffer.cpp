#include "stdafx.h"
#include "ImageBuffer.h"


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

void ImageBuffer::clearWithColor(uint32_t & color)
{
	for (auto &pixColor : colors)
		pixColor = color;
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
