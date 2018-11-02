#include "stdafx.h"
#include "ImageBuffer.h"

#include <algorithm>

union colorU
{
	uint32_t uint32;
	uint8_t colors[4];
};

constexpr uint8_t maxColor = 255;

ImageBuffer::ImageBuffer(uint16_t width, uint16_t height) :
	m_height{height},
	m_width{width}
{
	colors.clear();
	depths.resize(width * height, std::numeric_limits<float>::min());
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

void ImageBuffer::rasterize(const float3 &t1, const float3 &t2, const float3 &t3, const float4 &t1Color, const float4 &t2Color, const float4 &t3Color)
{
	auto uintT1Color = toUintColor(t1Color);
	auto uintT2Color = toUintColor(t2Color);
	auto uintT3Color = toUintColor(t3Color);

	int t1x = int((1 + t1.x) * m_width * 0.5f);
	int t1y = int((1 + t1.y) * m_height * 0.5f);

	int t2x = int((1 + t2.x) * m_width * 0.5f);
	int t2y = int((1 + t2.y) * m_height * 0.5f);

	int t3x = int((1 + t3.x) * m_width * 0.5f);
	int t3y = int((1 + t3.y) * m_height * 0.5f);

	int dx12 = t1x - t2x;
	int dx23 = t2x - t3x;
	int dx31 = t3x - t1x;

	const int dy12 = t1y - t2y;
	const int dy23 = t2y - t3y;
	const int dy31 = t3y - t1y;

	int minx = std::min({ t1x, t2x, t3x });
	int miny = std::min({ t1y, t2y, t3y });
	int maxx = std::max({ t1x, t2x, t3x });
	int maxy = std::max({ t1y, t2y, t3y });

	minx = std::max(minx, 0);
	maxx = std::min(maxx, m_width - 1);
	miny = std::max(miny, 0);
	maxy = std::min(maxy, m_height - 1 );

	int sum = 0;
	for (int i = minx; i < maxx; ++i)
	{
		for (int j = miny; j < maxy; ++j)
		{
			if (dx12 * (j - t1y) - dy12 * (i - t1x) > 0)
				continue;
			if (dx23 * (j - t2y) - dy23 * (i - t2x) > 0)
				continue;
			if (dx31 * (j - t3y) - dy31 * (i - t3x) > 0)
				continue;

			int indice = j * m_width + i;
			float depth = interpolateDepth(t1, t2, t3);

			//if (depths[indice] < depth)
			//	continue;
			depths.at(indice) = depth;
			colors.at(indice) = uintT1Color;
		}
	}

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

float ImageBuffer::interpolateDepth(const float3 & t1, const float3 & t2, const float3 & t3) const
{
	return 0.0f;
}

uint32_t ImageBuffer::toUintColor(const float4 & color) const
{
	colorU c;
	c.colors[3] = color.a * maxColor;
	c.colors[2] = color.x * maxColor;
	c.colors[1] = color.y * maxColor;
	c.colors[0] = color.z * maxColor;

	return c.uint32;
}
