#pragma once
#include "VertexProcessor.h"
#include "float4.h"

class Light
{
public:
	static float3 ambient;

	Light(const float3 position, const float3 color) :
		m_position{position},
		m_color{color}
	{
	}
	virtual ~Light() {}

	virtual float3 calculateLight(const float3 position,  const float3& normal) const = 0;
	virtual float3 calculateLight(const float3 position,  const float3& norma, const VertexProcessor& vp) const = 0;

protected:
	float3 m_position;
	float3 m_color;
};