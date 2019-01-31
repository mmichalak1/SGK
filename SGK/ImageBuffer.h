#pragma once
#include <vector>

#include "Vertex.h"
#include "VertexProcessor.h"
#include "Light.h"

struct Color {
	uint8_t R;
	uint8_t G;
	uint8_t B;
};

class ImageBuffer
{
public:
	ImageBuffer(uint16_t width, uint16_t height);
	~ImageBuffer();

	void clearWithColor(const float3 & clearColor);

	void rasterize(const float3 &t1, const float3 &t2, const float3 &t3,
		float3 color = { 1.0f, 0.0f, 0.0f }, float3 t2Color = { 0.0f, 1.0f, 0.0f }, float3 t3Color = { 0.0f, 0.0f, 1.0f });

	void rasterizePerPix(const Vertex & t1, const Vertex & t2, const Vertex & t3, const VertexProcessor& vp, const Light & light);

	void rasterize(const float3& v1, const float3& v2, const float3& v3, const VertexProcessor& vertProc);
	void rasterize(const Vertex& v1, const Vertex& v2, const Vertex& v3, const VertexProcessor& vertProc, const Light& light);

	std::vector<Color>* getColors();
	uint16_t getWidth() const;
	uint16_t getHeigth() const;

private:
	std::vector<float> depths;
	std::vector<Color> colors;

	uint16_t m_width;
	uint16_t m_height;

	uint32_t toColor(const float4 &color) const;
	uint32_t toColor(const float3 & color) const;
	Color toColorS(const float3 & color) const;
};

