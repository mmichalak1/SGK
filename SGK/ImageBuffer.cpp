#include "stdafx.h"
#include "ImageBuffer.h"

#include <algorithm>

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

void ImageBuffer::rasterize(const float3 &t1, const float3 &t2, const float3 &t3, const float4 &color)
{
	auto uintColor = toUintColor(color);

	float t1x = (1 + t1.x) * m_width * 0.5f;
	float t1y = (1 + t1.y) * m_height * 0.5f;

	float t2x = (1 + t2.x) * m_width * 0.5f;
	float t2y = (1 + t2.y) * m_height * 0.5f;

	float t3x = (1 + t3.x) * m_width * 0.5f;
	float t3y = (1 + t3.y) * m_height * 0.5f;

	float minx = std::min({ t1x, t2x, t3x });
	float miny = std::min({ t1y, t2y, t3y });
	float maxx = std::max({ t1x, t2x, t3x });
	float maxy = std::max({ t1y, t2y, t3y });

	minx = std::max(minx, 0.0f);
	maxx = std::min(maxx, float(m_width - 1));
	miny = std::max(miny, 0.0f);
	maxy = std::min(maxy, float( m_height - 1 ));

	for (float i = minx; i < maxx; ++i)
	{
		for (float j = miny; j < maxy; ++j)
		{
			if ((t1x - t2x) * (j - t1y) - (t1y - t2y) * (i - t1x) < 0.0f)
				continue;
			if ((t2x - t3x) * (j - t2y) - (t2y - t3y) * (i - t2x) < 0.0f)
				continue;
			if ((t3x - t1x) * (j - t3y) - (t3y - t1y) * (i - t3x) < 0.0f)
				continue;

			int indice = j * m_width + i;
			float depth = interpolateDepth(t1, t2, t3);
			//if (depths[indice] < depth)
			//	continue;
			depths.at(indice) = depth;
			colors.at(indice) = uintColor;
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
	c.colors[3] = color.a * 255;
	c.colors[2] = color.x * 255;
	c.colors[1] = color.y * 255;
	c.colors[0] = color.z * 255;

	return c.uint32;
}
