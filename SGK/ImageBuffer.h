#pragma once
#include <vector>

#include "Vertex.h"
#include "VertexProcessor.h"
#include "PointLight.h"

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

	void clearWithColor(const uint32_t &color);

	void rasterize(const float3 &t1, const float3 &t2, const float3 &t3,
		float4 color = float4( 1.0f, 1.0f, 0.0f, 0.0f ), float4 t2Color = { 1.0f, 0.0f, 1.0f, 0.0f }, float4 t3Color = { 1.0f, 0.0f, 0.0f, 1.0f });

	void rasterize(const float3& v1, const float3& v2, const float3& v3, const VertexProcessor& vertProc);
	void rasterize(const Vertex& v1, const Vertex& v2, const Vertex& v3, const VertexProcessor& vertProc, const PointLight& light);

	std::vector<uint32_t>* getColors();
	uint16_t getWidth() const;
	uint16_t getHeigth() const;

private:

	float4 calcluateLight(const float3& position, float3 normal, const PointLight& light) const;

	std::vector<float> depths;
	std::vector<uint32_t> colors;

	uint16_t m_width;
	uint16_t m_height;

	uint32_t toColor(const float4 &color) const;
};

