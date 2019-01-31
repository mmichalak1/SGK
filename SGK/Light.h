#pragma once
#include "VertexProcessor.h"
#include "float4.h"

class Light
{
public:
	static float3 ambient;

	Light(const float3 position, const float3 color, const float intensity, const int specPow) :
		m_position{position},
		m_color{color},
		m_intensity{intensity},
		m_specPow{specPow}
	{
	}
	virtual ~Light() {}

	virtual float3 calculateLight(const float3 position,  const float3& normal) const = 0;
	virtual float3 calculateLight(const float3 position,  const float3& norma, const VertexProcessor& vp) const = 0;
	virtual float3 calculateLightNoClamps(const float3 position, const float3& norma, const VertexProcessor& vp) const = 0;

protected:
	float3 m_position;
	float3 m_color;
	float m_intensity;
	int m_specPow;
};