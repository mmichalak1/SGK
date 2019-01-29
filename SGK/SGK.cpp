// SGK.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "ImageBuffer.h"
#include "TGASaver.h"
#include "VertexProcessor.h"
#include "Math.h"
#include "OBJLoader.h"

#include <chrono>
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

#undef TESTSPEED

using Clock = std::chrono::high_resolution_clock;
using duration = std::chrono::duration<double>;

constexpr float aspect = 16.0f / 9.0f;

void testMath()
{
	auto vecToNorm = float3{ 3, 3, 3 };
	vecToNorm.normalizeSelf();
	cout << vecToNorm << endl;


	auto vecToMul = float4{ 3.f, 1.f, 0.25f, 14.f };
	auto matToMul = float4x4{
	{2, 3, 1, 0},
	{2, 5,6,7},
	{1,5,2, 6},
	{6,8,3,2} };

	cout << "HERE\n";
	cout << mul(vecToMul, matToMul) <<endl;
	cout << fastMul(vecToMul, matToMul)<<endl;

	cout << transpose(matToMul);

	//cin.get();
}

void testVertexProcessor()
{
	auto imgBuffer = ImageBuffer(50, 50);
	auto vertProc = VertexProcessor();

	vertProc.setPerspective(45.0f, 9.f / 6.f, 1.0f, 100.0f);
	vertProc.setLookAt({ 0.0f, 30.0f, -150.f }, { 0.0f, 0.0f, -25.0f });
	vertProc.update();

	vertProc.printData();
	//cin.get();
}

void testDrawSimpleTriangle()
{
	auto imageBuffer = ImageBuffer(800, 600);
	uint32_t clearColor = uint32_t{ 0xff000000 };
	auto vertexProcessor = VertexProcessor();

		vertexProcessor.setPerspective(90.0f, aspect, 1.0f, 100.0f);
	vertexProcessor.setLookAt({ 0.0f, 0.0f, -50.0f }, { 0.0f, 0.0f, 1.f });
	vertexProcessor.update();

	const auto v1 = Vertex{ { 15.f, 10.0f, 0.f },  {0.f,0.f, 0.f} };
	const auto v2 = Vertex{ {-15.f, 10.f, 0.f }, {0.f,0.f, 0.f} };
	const auto v3 = Vertex{ {  0.f, -8.f, 0.f },  {0.f,0.f, 0.f} };

	imageBuffer.rasterize(v1.position, v2.position, v3.position, vertexProcessor);

	TGASaver::saveToFile("simpleTest", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());
}

void testTransform()
{
	auto imageBuffer = ImageBuffer(800, 600);
	uint32_t clearColor = uint32_t{ 0xff000000 };
	auto vertexProcessor = VertexProcessor();

	vertexProcessor.setPerspective(45.0f, aspect, 1.0f, 100.0f);
	vertexProcessor.setLookAt({ 0.0f, 0.0f, -50.0f }, { 0.0f, 0.0f, 1.f });
	vertexProcessor.update();

	const auto v1 = Vertex{ { 15.f, 10.0f, 0.f },  {0.f,0.f, 0.f} };
	const auto v2 = Vertex{ {-15.f, 10.f, 0.f },   {0.f,0.f, 0.f} };
	const auto v3 = Vertex{ {  0.f, -8.f, 0.f },   {0.f,0.f, 0.f} };

	vertexProcessor.multByTransl({ 0, 5, 10 });
	vertexProcessor.multByScale({ 0.4f, 0.5f, 0.7f });
	vertexProcessor.multByRot(45.f, { 0.f, 1.f, 0.f });

	imageBuffer.rasterize(v1.position, v2.position, v3.position, vertexProcessor);
	TGASaver::saveToFile("roationTest", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());
}

void testVertexLighting()
{
	auto imageBuffer = ImageBuffer(800, 600);

	uint32_t clearColor = uint32_t{ 0xff000057 };
	imageBuffer.clearWithColor(clearColor);

	auto vertexProcessor = VertexProcessor();

	vertexProcessor.setPerspective(45.0f, aspect, 1.0f, 100.0f);
	vertexProcessor.setLookAt({ 0.0f, 0.0f, -50.0f }, { 1.0f, 1.0f, 1.f });
	vertexProcessor.update();

	vertexProcessor.multByRot(45.f, { 1.f, 1.f, 0.f });
	vertexProcessor.multByScale({ 10.f, 10.f, 10.f });

	auto cube = Mesh::createCube();
	auto light = PointLight({ 1.f, 1.f, 1.f }, {3.f, -5.f, 0.f}, 1.f);
	cube.draw(imageBuffer, vertexProcessor, light);

	TGASaver::saveToFile("vertexLight", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());
}

void testPixelShading()
{
	auto imageBuffer = ImageBuffer(800, 600);

	uint32_t clearColor = uint32_t{ 0xff000057 };
	imageBuffer.clearWithColor(clearColor);

	auto vertexProcessor = VertexProcessor();

	vertexProcessor.setPerspective(45.0f, aspect, 1.0f, 100.0f);
	vertexProcessor.setLookAt({ 0.0f, 0.0f, -50.0f }, { 1.0f, 1.0f, 1.f });

	vertexProcessor.multByRot(45.f, { 1.f, 1.f, 0.f });
	vertexProcessor.multByScale({ 10.f, 10.f, 10.f });

	auto cube = Mesh::createCube();
	auto light = PointLight({ 0.f, 1.f, 0.f }, { 3.f, -5.f, 0.f }, 1.f);
	cube.drawPerPix(imageBuffer, vertexProcessor, light);

	TGASaver::saveToFile("vertexLight", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());
}

void testRotSpeed()
{
	auto vertexProcessor = VertexProcessor();

	vertexProcessor.setPerspective(45.0f, aspect, 1.0f, 100.0f);
	auto slowStart = Clock::now();
	for(float i =0.f; i< 5000.f; ++i)
		vertexProcessor.multByRot(i, { 1.0f, 1.0f, 1.f });
	auto slowEnd = Clock::now();

	auto fastStart = Clock::now();
	for (float i = 0.f; i < 5000.f; ++i)
		vertexProcessor.fastMulByRot(i, { 1.0f, 1.0f, 1.f });
	auto fastEnd = Clock::now();


	std::cout << "rot matrtix mul optmialization: "
		<< std::chrono::duration_cast<duration>(slowEnd - slowStart).count() / std::chrono::duration_cast<duration>(fastEnd - fastStart).count()
		<< endl;

}

void testMatrixMul()
{
	auto vecToMul = float4{ 3.f, 1.f, 0.25f, 14.f };
	auto matToMul = float4x4{
	{2, 3, 1, 0},
	{2, 5,6,7},
	{1,5,2, 6},
	{6,8,3,2} };

	auto slowStart = Clock::now();
	for (float i = 0.f; i < 5000.f; ++i)
		mul(vecToMul, matToMul);
	auto slowEnd = Clock::now();

	auto fastStart = Clock::now();
	for (float i = 0.f; i < 5000.f; ++i)
		fastMul(vecToMul, matToMul);
	auto fastEnd = Clock::now();


	std::cout << "matrix vector multiplication optmialization: "
		<< std::chrono::duration_cast<duration>(slowEnd - slowStart).count() / std::chrono::duration_cast<duration>(fastEnd - fastStart).count()
		<< endl;


}

int main()
{
	auto timerStart = Clock::now();

#ifdef TESTMATH
	testMath();
#endif // TESTMATH

#ifdef TESTVERPROC
	testVertexProcessor();
#endif // TESTVERPROC

#ifdef TESTSIMPLEDRAW
	testDrawSimpleTriangle();
	testTransform();
	testVertexLighting();
#endif // TESTSIMPLEDRAW

#ifdef TESTSPEED
	testRotSpeed();
	testMatrixMul();
	cin.get();
	return 0;
#endif

	auto imageBuffer = ImageBuffer(800, 600);

	uint32_t clearColor = uint32_t{ 0xff000057 };
	imageBuffer.clearWithColor(clearColor);

	auto vertexProcessor = VertexProcessor();

	vertexProcessor.setPerspective(45.0f, aspect, 1.0f, 100.0f);
	vertexProcessor.setLookAt({ 0.0f, 0.0f, -50.0f }, { 1.0f, 1.0f, 1.f });
	vertexProcessor.update();

	vertexProcessor.multByScale({ 10.f, 10.f, 10.f });
	vertexProcessor.multByRot(45.f, { 1.f, 1.f, 0.f });
	//vertexProcessor.multByTransl({20.f, 5.f, 0.f});
	auto cube = Mesh::createCube();

	cube.drawPerPix(imageBuffer, vertexProcessor, PointLight{ {1.0f, 1.f, 1.f}, {0.f, 0.f, -10.f}, 0.3f });

	auto timerEnd = Clock::now();
	auto time = std::chrono::duration_cast<duration>(timerEnd - timerStart);

	std::cout << "Rendered in: " << time.count();
	TGASaver::saveToFile("lamared", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());
	//std::cin.get();
	return 0;
}

