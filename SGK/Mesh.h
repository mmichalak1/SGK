#pragma once
#include "ImageBuffer.h"
#include "int3.h"
#include "PointLight.h"
#include <vector>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void draw(ImageBuffer& imgBuff, const VertexProcessor& processor);
	void draw(ImageBuffer& imgBuff, const VertexProcessor& processor, const PointLight &pointLight);
	void drawPerPix(ImageBuffer & buffer, const VertexProcessor & vp, const Light & light);
	void calculateNormal();

	static Mesh createCube();

private:
	std::vector<Vertex> m_verticies;
	std::vector<int3> m_indices;
};

