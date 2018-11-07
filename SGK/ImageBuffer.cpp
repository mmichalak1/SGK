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
	m_height{ height },
	m_width{ width }
{
	colors.clear();
	depths.resize(width * height, 1000.f);
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

void ImageBuffer::rasterize(const float3 &t1, const float3 &t2, const float3 &t3, float4 t1Color, float4 t2Color, float4 t3Color)
{
	float t1x = (1 + t1.x) * m_width * 0.5f;
	float t1y = (1 + t1.y) * m_height * 0.5f;

	float t2x = (1 + t2.x) * m_width * 0.5f;
	float t2y = (1 + t2.y) * m_height * 0.5f;

	float t3x = (1 + t3.x) * m_width * 0.5f;
	float t3y = (1 + t3.y) * m_height * 0.5f;

	const float dx12 = t1x - t2x;
	const float dx23 = t2x - t3x;
	const float dx31 = t3x - t1x;

	const float dy12 = t1y - t2y;
	const float dy23 = t2y - t3y;
	const float dy31 = t3y - t1y;

	float minx = std::min({ t1x, t2x, t3x });
	float miny = std::min({ t1y, t2y, t3y });
	float maxx = std::max({ t1x, t2x, t3x });
	float maxy = std::max({ t1y, t2y, t3y });

	minx = std::max(minx, 0.f);
	maxx = std::min(maxx, float(m_width - 1));
	miny = std::max(miny, 0.f);
	maxy = std::min(maxy, float(m_height - 1));

	bool tl1 = false;
	bool tl2 = false;
	bool tl3 = false;

	for (int i = minx; i < maxx; ++i)
	{
		for (int j = miny; j < maxy; ++j)
		{
			if (dy12 < 0.f || (dy12 == 0 && dx12 > 0.f))
				tl1 = true;
			if (dy23 < 0.f || (dy23 == 0 && dx23 > 0.f))
				tl2 = true;
			if (dy31 < 0.f || (dy31 == 0 && dx31 > 0.f))
				tl3 = true;

			if (!tl1)
				if (dx12 * (j - t1y) - dy12 * (i - t1x) > 0)
					continue;
			if (!tl2)
				if (dx23 * (j - t2y) - dy23 * (i - t2x) > 0)
					continue;
			if (!tl3)
				if (dx31 * (j - t3y) - dy31 * (i - t3x) > 0)
					continue;

			const float lambda1 = (dy23 * (i - t3x) + (t3x - t2x) * (j - t3y)) / (dy23 * (t1x - t3x) + (t3x - t2x) * (t1y - t3y));
			const float lambda2 = (dy31 * (i - t3x) + (t1x - t3x) * (j - t3y)) / (dy31 * dx23 + (t1x - t3x) * dy23);
			const float lambda3 = 1.f - lambda1 - lambda2;

			auto color = t1Color * lambda1 + t2Color * lambda2 + t3Color * lambda3;
			auto depth = t1.z * lambda1 + t2.z * lambda2 + t3.z * lambda3;

			int indice = j * m_width + i;
			if (depth < 0.0f)
				continue;
			if (depth > depths[indice])
				continue;
			depths[indice] = depth;
			colors.at(indice) = toUintColor(color);
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

uint32_t ImageBuffer::toUintColor(const float4 & color) const
{
	colorU c;
	c.colors[3] = color.a * maxColor;
	c.colors[2] = color.r * maxColor;
	c.colors[1] = color.g * maxColor;
	c.colors[0] = color.b * maxColor;

	return c.uint32;
}
