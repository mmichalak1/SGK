#include "stdafx.h"
#include "PointLight.h"


PointLight::PointLight(const float4 col, const float3 pos, float intens) :
	color{col},
	position{pos},
	intensity{intens}
{
}


PointLight::~PointLight()
{
}
