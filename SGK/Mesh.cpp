#include "stdafx.h"
#include "Mesh.h"
#include "Math.h"


Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::draw(ImageBuffer & imgBuff, const VertexProcessor & processor)
{
	for (const auto& triangle : m_indices)
	{
		imgBuff.rasterize(
			m_verticies[triangle.x].position,
			m_verticies[triangle.y].position,
			m_verticies[triangle.z].position,
			processor
		);
	}
}

void Mesh::draw(ImageBuffer & imgBuff, const VertexProcessor & processor, const PointLight& light)
{
	for (const auto& triangle : m_indices)
	{
		imgBuff.rasterize(
			m_verticies[triangle.x],
			m_verticies[triangle.y],
			m_verticies[triangle.z],
			processor,
			light
		);
	}
}

void Mesh::drawPerPix(ImageBuffer& buffer, const VertexProcessor& vp, const Light& light)
{
	for (const auto& triangle : m_indices)
	{
		buffer.rasterizePerPix(
			m_verticies[triangle.x],
			m_verticies[triangle.y],
			m_verticies[triangle.z],
			vp,
			light
		);
	}
}

void Mesh::drawModelPerPix(ImageBuffer& buffer, const VertexProcessor& vp, const Light& light) const
{
	for (int i = 0; i < m_indices.size(); i++)
	{
		auto v1 = Vertex{ m_positions[m_indices[i].x], m_normals[m_normalIndices[i].x] };
		auto v2 = Vertex{ m_positions[m_indices[i].y], m_normals[m_normalIndices[i].y] };
		auto v3 = Vertex{ m_positions[m_indices[i].z], m_normals[m_normalIndices[i].z] };

		buffer.rasterizePerPix(
			v1,
			v2,
			v3,
			vp,
			light
		);
	}
}

void Mesh::drawModelPerPix(ImageBuffer& buffer, const VertexProcessor& vp, const std::vector<Light*>& lights) const
{
	for (int i = 0; i < m_indices.size(); i++)
	{
		auto v1 = Vertex{ m_positions[m_indices[i].x], m_normals[m_normalIndices[i].x] };
		auto v2 = Vertex{ m_positions[m_indices[i].y], m_normals[m_normalIndices[i].y] };
		auto v3 = Vertex{ m_positions[m_indices[i].z], m_normals[m_normalIndices[i].z] };

		buffer.rasterizePerPix(
			v1,
			v2,
			v3,
			vp,
			lights
		);
	}

}


void Mesh::calculateNormal()
{
	for (const auto& triangle : m_indices)
	{
		auto n = normalize(
			cross(m_verticies[triangle.z].position - m_verticies[triangle.x].position,
				m_verticies[triangle.y].position - m_verticies[triangle.x].position));

		m_verticies[triangle.x].normal += n;
		m_verticies[triangle.y].normal += n;
		m_verticies[triangle.z].normal += n;
	}

	for (auto& vertex : m_verticies)
		vertex.normal.normalizeSelf();
}

void Mesh::loadData(std::vector<float3>& positions,
	const std::vector<float3>& normals,
	std::vector<int3> indices,
	std::vector<int3> normalIndices)
{
	m_indices = indices;
	m_normalIndices = normalIndices;
	m_positions = positions;
	m_normals = normals;
}

void Mesh::reverse()
{
	for (auto& normal : m_normals)
		normal *= -1.f;
}

Mesh Mesh::createCube()
{
	auto result = Mesh();

	result.m_verticies.emplace_back(float3{ -0.5f, -0.5f, -0.5f }, float3{ 0.f, 0.f, 0.f }); //0-0
	result.m_verticies.emplace_back(float3{ -0.5f, -0.5f,  0.5f }, float3{ 0.f, 0.f, 0.f });  //4-1
	result.m_verticies.emplace_back(float3{ -0.5f,  0.5f, -0.5f }, float3{ 0.f, 0.f, 0.f }); //1-2
	result.m_verticies.emplace_back(float3{ -0.5f,  0.5f,  0.5f }, float3{ 0.f, 0.f, 0.f });  //5-3

	result.m_verticies.emplace_back(float3{ 0.5f, -0.5f, -0.5f }, float3{ 0.f, 0.f, 0.f }); //2-4
	result.m_verticies.emplace_back(float3{ 0.5f, -0.5f,  0.5f }, float3{ 0.f, 0.f, 0.f });  //6-5
	result.m_verticies.emplace_back(float3{ 0.5f,  0.5f, -0.5f }, float3{ 0.f, 0.f, 0.f }); //3-6
	result.m_verticies.emplace_back(float3{ 0.5f,  0.5f,  0.5f }, float3{ 0.f, 0.f, 0.f });  //7-7

	result.m_indices.push_back({ 0, 6, 4 });
	result.m_indices.push_back({ 0, 2, 6 });
	result.m_indices.push_back({ 0, 3, 2 });
	result.m_indices.push_back({ 0, 1, 3 });
	result.m_indices.push_back({ 2, 7, 6 });
	result.m_indices.push_back({ 2, 3, 7 }); //n
	result.m_indices.push_back({ 4, 6, 7 }); //n
	result.m_indices.push_back({ 4, 7, 5 }); //
	result.m_indices.push_back({ 0, 4, 5 }); //
	result.m_indices.push_back({ 0, 5, 1 });
	result.m_indices.push_back({ 1, 5, 7 });
	result.m_indices.push_back({ 1, 7, 3 });

	result.calculateNormal();

	return result;
}
