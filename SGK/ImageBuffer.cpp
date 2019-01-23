#include "stdafx.h"
#include "ImageBuffer.h"
#include "Math.h"

#include <algorithm>

union colorU
{
	uint32_t uint32;
	struct
	{
		uint8_t A;
		uint8_t R;
		uint8_t G;
		uint8_t B;
	} ARGB;
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
	float t1x = (1.f + t1.x) * m_width * 0.5f;
	float t1y = (1.f + t1.y) * m_height * 0.5f;

	float t2x = (1.f + t2.x) * m_width * 0.5f;
	float t2y = (1.f + t2.y) * m_height * 0.5f;

	float t3x = (1.f + t3.x) * m_width * 0.5f;
	float t3y = (1.f + t3.y) * m_height * 0.5f;

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

	bool tl1 = dy12 < 0. || (dy12 == 0 && dx12 > 0);
	bool tl2 = dy23 < 0. || (dy23 == 0 && dx23 > 0);
	bool tl3 = dy31 < 0. || (dy31 == 0 && dx31 > 0);

	for (int i = minx; i < maxx; ++i)
	{
		for (int j = miny; j < maxy; ++j)
		{
			if (((dx12 * (j - t1y) - dy12 * (i - t1x) > 0 && !tl1) || (dx12 * (j - t1y) - dy12 * (i - t1x) >=0) && tl1) &&
				((dx23 * (j - t2y) - dy23 * (i - t2x) > 0 && !tl2) || (dx23 * (j - t2y) - dy23 * (i - t2x) >=0) && tl2) &&
				((dx31 * (j - t3y) - dy31 * (i - t3x) > 0 && !tl3) || (dx31 * (j - t3y) - dy31 * (i - t3x) >=0) && tl3))
			{

				const float lambda1 = (dy23 * (i - t3x) + (t3x - t2x) * (j - t3y)) / (dy23 * (t1x - t3x) + (t3x - t2x) * (t1y - t3y));
				const float lambda2 = (dy31 * (i - t3x) + (t1x - t3x) * (j - t3y)) / (dy31 * dx23 + (t1x - t3x) * dy23);
				const float lambda3 = 1.f - lambda1 - lambda2;

				auto depth = t1.z * lambda1 + t2.z * lambda2 + t3.z * lambda3;

				int indice = j * m_width + i;
				if(depth < depths[indice])
				{
					colors[indice] = toColor(t1Color * lambda1 + t2Color * lambda2 + t3Color * lambda3);
					depths[indice] = depth;
				}
			}
		}
	}

}

void ImageBuffer::rasterize(const float3 & v1, const float3 & v2, const float3 & v3, const VertexProcessor & vertProc)
{
	rasterize(
		vertProc.triangle(v1),
		vertProc.triangle(v2),
		vertProc.triangle(v3),
		{1.f, 0.f, 0.f, 0.f},
		{1.f, 0.f, 0.f, 0.f},
		{1.f, 0.f, 0.f, 0.f}
	);
}

void ImageBuffer::rasterize(const Vertex& v1, const Vertex & v2, const Vertex & v3, const VertexProcessor & vertProc, const PointLight& light)
{
	rasterize(
		vertProc.triangle(v1.position),
		vertProc.triangle(v2.position),
		vertProc.triangle(v3.position),
		calcluateLight(vertProc.vertexToWorld(v1.position), vertProc.vertexToWorld(v1.normal), light),
		calcluateLight(vertProc.vertexToWorld(v2.position), vertProc.vertexToWorld(v2.normal), light),
		calcluateLight(vertProc.vertexToWorld(v3.position), vertProc.vertexToWorld(v3.normal), light)
	);
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

float4 ImageBuffer::calcluateLight(const float3& position, float3 normal, const PointLight& light) const
{

	auto toLight =  light.position - position;
	toLight.normalizeSelf();
	normal.normalizeSelf();
	auto angle = dot(normal, toLight);

	angle = std::max(angle, 0.f);

	auto result = light.color * angle * light.intensity;
	float4 color = float4{ 1.f, 1.f, 1.f, 1.f };

	result = color * result;

	result.clamp(0.f, 1.0f);
	return result;
}

uint32_t ImageBuffer::toColor(const float4 & color) const
{
	colorU c;
	c.ARGB.A = uint8_t(color.a * maxColor);
	c.ARGB.R = uint8_t(color.r * maxColor);
	c.ARGB.G = uint8_t(color.g * maxColor);
	c.ARGB.B = uint8_t(color.b * maxColor);

	return c.uint32;
}
