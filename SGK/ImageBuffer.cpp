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

static_assert(sizeof(colorU) == 4, "Wrong size of colorU");

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

void ImageBuffer::clearWithColor(const float3 & clearColor)
{
	auto color = toColorS(clearColor);
	for (auto &pixColor : colors)
		pixColor = color;
}

void ImageBuffer::rasterize(const float3 &t1, const float3 &t2, const float3 &t3, float3 t1Color, float3 t2Color, float3 t3Color)
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
			if (((dx12 * (j - t1y) - dy12 * (i - t1x) > 0 && !tl1) || (dx12 * (j - t1y) - dy12 * (i - t1x) >= 0) && tl1) &&
				((dx23 * (j - t2y) - dy23 * (i - t2x) > 0 && !tl2) || (dx23 * (j - t2y) - dy23 * (i - t2x) >= 0) && tl2) &&
				((dx31 * (j - t3y) - dy31 * (i - t3x) > 0 && !tl3) || (dx31 * (j - t3y) - dy31 * (i - t3x) >= 0) && tl3))
			{

				const float lambda1 = (dy23 * (i - t3x) + (t3x - t2x) * (j - t3y)) / (dy23 * (t1x - t3x) + (t3x - t2x) * (t1y - t3y));
				const float lambda2 = (dy31 * (i - t3x) + (t1x - t3x) * (j - t3y)) / (dy31 * dx23 + (t1x - t3x) * dy23);
				const float lambda3 = 1.f - lambda1 - lambda2;

				auto depth = t1.z * lambda1 + t2.z * lambda2 + t3.z * lambda3;

				int indice = j * m_width + i;
				if (depth < depths[indice])
				{
					colors[indice] = toColorS(t1Color * lambda1 + t2Color * lambda2 + t3Color * lambda3);
					depths[indice] = depth;
				}
			}
		}
	}

}

void ImageBuffer::rasterizePerPix(const Vertex &v1, const Vertex &v2, const Vertex &v3, const VertexProcessor& vp, const Light& light)
{
	float3 t1 = vp.triangle(v1.position);
	float t1x = (1.f + t1.x) * m_width * 0.5f;
	float t1y = (1.f + t1.y) * m_height * 0.5f;

	float3 t2 = vp.triangle(v2.position);
	float t2x = (1.f + t2.x) * m_width * 0.5f;
	float t2y = (1.f + t2.y) * m_height * 0.5f;

	float3 t3 = vp.triangle(v3.position);
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
			if (((dx12 * (j - t1y) - dy12 * (i - t1x) > 0 && !tl1) || (dx12 * (j - t1y) - dy12 * (i - t1x) >= 0) && tl1) &&
				((dx23 * (j - t2y) - dy23 * (i - t2x) > 0 && !tl2) || (dx23 * (j - t2y) - dy23 * (i - t2x) >= 0) && tl2) &&
				((dx31 * (j - t3y) - dy31 * (i - t3x) > 0 && !tl3) || (dx31 * (j - t3y) - dy31 * (i - t3x) >= 0) && tl3))
			{

				const float lambda1 = (dy23 * (i - t3x) + (t3x - t2x) * (j - t3y)) / (dy23 * (t1x - t3x) + (t3x - t2x) * (t1y - t3y));
				const float lambda2 = (dy31 * (i - t3x) + (t1x - t3x) * (j - t3y)) / (dy31 * dx23 + (t1x - t3x) * dy23);
				const float lambda3 = 1.f - lambda1 - lambda2;

				auto depth = t1.z * lambda1 + t2.z * lambda2 + t3.z * lambda3;

				int indice = j * m_width + i;
				if (depth < depths[indice])
				{
					auto position = v1.position * lambda1 + v2.position * lambda2 + v3.position * lambda3;
					auto normal = v1.normal * lambda1 + v2.normal * lambda2 + v3.normal * lambda3;
					colors[indice] = toColorS(light.calculateLight(position, normal, vp));
					depths[indice] = depth;
				}
			}
		}
	}

}

void ImageBuffer::rasterizePerPix(const Vertex &v1, const Vertex &v2, const Vertex &v3, const VertexProcessor& vp, const std::vector<Light*>& lights)
{
	float3 t1 = vp.triangle(v1.position);
	float t1x = (1.f + t1.x) * m_width * 0.5f;
	float t1y = (1.f + t1.y) * m_height * 0.5f;

	float3 t2 = vp.triangle(v2.position);
	float t2x = (1.f + t2.x) * m_width * 0.5f;
	float t2y = (1.f + t2.y) * m_height * 0.5f;

	float3 t3 = vp.triangle(v3.position);
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
			if (((dx12 * (j - t1y) - dy12 * (i - t1x) > 0 && !tl1) || (dx12 * (j - t1y) - dy12 * (i - t1x) >= 0) && tl1) &&
				((dx23 * (j - t2y) - dy23 * (i - t2x) > 0 && !tl2) || (dx23 * (j - t2y) - dy23 * (i - t2x) >= 0) && tl2) &&
				((dx31 * (j - t3y) - dy31 * (i - t3x) > 0 && !tl3) || (dx31 * (j - t3y) - dy31 * (i - t3x) >= 0) && tl3))
			{

				const float lambda1 = (dy23 * (i - t3x) + (t3x - t2x) * (j - t3y)) / (dy23 * (t1x - t3x) + (t3x - t2x) * (t1y - t3y));
				const float lambda2 = (dy31 * (i - t3x) + (t1x - t3x) * (j - t3y)) / (dy31 * dx23 + (t1x - t3x) * dy23);
				const float lambda3 = 1.f - lambda1 - lambda2;

				auto depth = t1.z * lambda1 + t2.z * lambda2 + t3.z * lambda3;

				int indice = j * m_width + i;
				if (depth < depths[indice])
				{
					auto position = v1.position * lambda1 + v2.position * lambda2 + v3.position * lambda3;
					auto normal = v1.normal * lambda1 + v2.normal * lambda2 + v3.normal * lambda3;

					auto color = Light::ambient;
					for (const auto& light : lights)
					{
						color += light->calculateLightNoClamps(position, normal, vp);
					}
					color.clampSelf();
					colors[indice] = toColorS(color);
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
		{ 1.f, 1.f, 1.f },
		{ 1.f, 1.f, 1.f },
		{ 1.f, 1.f, 1.f }
	);
}

void ImageBuffer::rasterize(const Vertex& v1, const Vertex & v2, const Vertex & v3, const VertexProcessor & vertProc, const Light& light)
{
	rasterize(
		vertProc.triangle(v1.position),
		vertProc.triangle(v2.position),
		vertProc.triangle(v3.position),
		light.calculateLight(vertProc.vertexToWorld(v1.position), vertProc.vertexToWorld(v1.normal)),
		light.calculateLight(vertProc.vertexToWorld(v2.position), vertProc.vertexToWorld(v2.normal)),
		light.calculateLight(vertProc.vertexToWorld(v3.position), vertProc.vertexToWorld(v3.normal))
	);
}

std::vector<Color>* ImageBuffer::getColors()
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

uint32_t ImageBuffer::toColor(const float4 & color) const
{
	colorU c;
	c.ARGB.A = maxColor;
	c.ARGB.R = maxColor - uint8_t(color.r * maxColor);
	c.ARGB.G = maxColor - uint8_t(color.g * maxColor);
	c.ARGB.B = maxColor - uint8_t(color.b * maxColor);

	return c.uint32;
}

uint32_t ImageBuffer::toColor(const float3 & color) const
{
	colorU c;
	c.ARGB.A = 255;
	c.ARGB.R = uint8_t(color.x * maxColor);
	c.ARGB.G = uint8_t(color.y * maxColor);
	c.ARGB.B = uint8_t(color.z * maxColor);

	return c.uint32;
}

Color ImageBuffer::toColorS(const float3 & color) const
{
	return Color{
		uint8_t(color.x * maxColor),
		uint8_t(color.y * maxColor),
		uint8_t(color.z *maxColor)
	};
}
