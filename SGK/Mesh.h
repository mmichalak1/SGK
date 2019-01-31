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
	void drawModelPerPix(ImageBuffer & buffer, const VertexProcessor & vp, const Light & light) const;
	void drawModelPerPix(ImageBuffer & buffer, const VertexProcessor & vp, const std::vector<Light*>& lights) const;
	void calculateNormal();

	void loadData(std::vector<float3>& positions, const std::vector<float3>& normals, std::vector<int3> indices, std::vector<int3> normalIndices);

	void reverse();

	static Mesh createCube();

private:
	std::vector<Vertex> m_verticies;
	std::vector<int3> m_indices;

	std::vector<float3> m_positions;
	std::vector<float3> m_normals;
	std::vector<int3> m_normalIndices;

};

