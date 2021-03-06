// SGK.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "ImageBuffer.h"
#include "TGASaver.h"
#include "VertexProcessor.h"
#include "Math.h"
#include "OBJLoader.h"

#include "DirectionalLight.h"

#include <chrono>
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

#undef TESTSPEED

using Clock = std::chrono::high_resolution_clock;
using duration = std::chrono::duration<double>;

constexpr float aspect = 4.0f / 3.0f;

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
	cout << reflect({ 3.f, 3.f, 3.f }, { 0.8f, 1.2f, 0.7f }) << endl;
	//cout << fastMul(vecToMul, matToMul)<<endl;

	//cout << transpose(matToMul);

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

	TGASaver::toPPM("simpleTest", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());
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
	TGASaver::toPPM("roationTest", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());
}

void testVertexLighting()
{
	auto imageBuffer = ImageBuffer(800, 600);

	imageBuffer.clearWithColor({ 1.f, 0.f, 0.f });

	auto vertexProcessor = VertexProcessor();

	vertexProcessor.setPerspective(45.0f, aspect, 1.0f, 100.0f);
	vertexProcessor.setLookAt({ 0.0f, 0.0f, -50.0f }, { 1.0f, 1.0f, 1.f });
	vertexProcessor.update();

	vertexProcessor.multByRot(45.f, { 1.f, 1.f, 0.f });
	vertexProcessor.multByScale({ 10.f, 10.f, 10.f });

	auto cube = Mesh::createCube();
	auto light = PointLight({ 1.f, 1.f, 1.f }, { 3.f, -5.f, 0.f }, 1.f, 10);
	cube.draw(imageBuffer, vertexProcessor, light);

	TGASaver::toPPM("vertexLight", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());
}

void testPixelShading()
{
	auto imageBuffer = ImageBuffer(800, 600);

	imageBuffer.clearWithColor({ 1.f, 0.f, 0.f });

	auto vertexProcessor = VertexProcessor();

	vertexProcessor.setPerspective(45.0f, aspect, 1.0f, 100.0f);
	vertexProcessor.setLookAt({ 0.0f, 0.0f, -50.0f }, { 1.0f, 1.0f, 1.f });

	vertexProcessor.multByRot(45.f, { 1.f, 1.f, 0.f });
	vertexProcessor.multByScale({ 10.f, 10.f, 10.f });

	auto cube = Mesh::createCube();
	auto light = PointLight({ 0.f, 1.f, 0.f }, { 3.f, -5.f, 0.f }, 1.f, 10);
	cube.drawPerPix(imageBuffer, vertexProcessor, light);

	TGASaver::toPPM("vertexLight", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());
}

void testRotSpeed()
{
	auto vertexProcessor = VertexProcessor();

	vertexProcessor.setPerspective(45.0f, aspect, 1.0f, 100.0f);
	auto slowStart = Clock::now();
	for (float i = 0.f; i < 1000000.f; ++i)
		vertexProcessor.multByRot(i, { 1.0f, 1.0f, 1.f });
	auto slowEnd = Clock::now();

	auto fastStart = Clock::now();
	for (float i = 0.f; i < 1000000.f; ++i)
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
	for (float i = 0.f; i < 1000000.f; ++i)
		mul(vecToMul, matToMul);
	auto slowEnd = Clock::now();

	auto fastStart = Clock::now();
	for (float i = 0.f; i < 1000000.f; ++i)
		fastMul(vecToMul, matToMul);
	auto fastEnd = Clock::now();


	std::cout << "matrix vector multiplication optmialization: "
		<< std::chrono::duration_cast<duration>(slowEnd - slowStart).count() / std::chrono::duration_cast<duration>(fastEnd - fastStart).count()
		<< endl;


}

void drawModel(ImageBuffer& buffer, VertexProcessor& vertProc, const float3& pos, const float3& scale,
	const float3& rot, const float angle, const Mesh& mesh, const Light& light)
{
	vertProc.setIdentity();
	vertProc.multByScale(scale);
	vertProc.multByRot(angle, rot);
	vertProc.multByTransl(pos);

	mesh.drawModelPerPix(buffer, vertProc, light);
}

void drawModel(ImageBuffer& buffer, VertexProcessor& vertProc, const float3& pos, const float3& scale,
	const float3& rot, const float angle, const Mesh& mesh, const std::vector<Light*>& light)
{
	vertProc.setIdentity();
	vertProc.multByScale(scale);
	vertProc.multByRot(angle, rot);
	vertProc.multByTransl(pos);

	mesh.drawModelPerPix(buffer, vertProc, light);
}

void drawSingleLight()
{
	auto imageBuffer = ImageBuffer(800, 600);

	imageBuffer.clearWithColor({ 0.0f, 0.0f, 0.0f });

	auto vertexProcessor = VertexProcessor();
	//auto sphere = OBJLoader::loadFromFile("sph.obj");
	auto kettle = OBJLoader::loadFromFile("teapot.obj");


	vertexProcessor.setPerspective(45.0f, aspect, 1.0f, 100.0f);
	vertexProcessor.setLookAt({ 0.0f, 0.0f, -50.0f }, { 1.0f, 1.0f, 1.f });

	vertexProcessor.update();

	auto pLight = PointLight{ {0.9f, 0.9f, .9f}, {0.f, 0.f, 0.f}, 0.4f, 5 };
	auto dLight = DirectionalLight{ {0.99f, 0.99f, 1.f}, {0.f, -0.999f, -0.0f}, 0.4f, 14 };

	auto light = &pLight;

	//drawModel(imageBuffer,
	//	vertexProcessor,
	//	{ -10.f, 0.f, 0.f }, //pos
	//	{ 10.f, 10.f, 10.f }, //scale
	//	{ 0.f, 1.f, 0.f }, //rotAxis
	//	90.f, //angle
	//	sphere,
	//	*light);

	drawModel(imageBuffer,
		vertexProcessor,
		{ 10.f, -5.f, 0.f },
		{ 3.f, 3.f, 3.f },
		{ 0.f, 1.f, 0.f },
		-90.f,
		kettle,
		*light);

	TGASaver::toPPM("singleLight", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());
}

int main()
{
	auto timerStart = Clock::now();

//#ifdef TESTMATH
//	testMath();
//#endif // TESTMATH
//
//#ifdef TESTVERPROC
//	testVertexProcessor();
//#endif // TESTVERPROC
//
//#ifdef TESTSIMPLEDRAW
//	testDrawSimpleTriangle();
//	testTransform();
//	testVertexLighting();
//#endif // TESTSIMPLEDRAW
//
//#ifdef TESTSPEED
//	testRotSpeed();
//	testMatrixMul();
//	cin.get();
//	return 0;
//#endif
//
	//drawSingleLight();
	//return 0;

	auto imageBuffer = ImageBuffer(800, 600);

	imageBuffer.clearWithColor({ 0.0f, 0.0f, 0.0f });

	auto vertexProcessor = VertexProcessor();
	auto sphere = OBJLoader::loadFromFile("sph.obj");
	auto kettle = OBJLoader::loadFromFile("teapot2.obj");


	vertexProcessor.setPerspective(45.0f, aspect, 1.0f, 100.0f);
	vertexProcessor.setLookAt({ 0.0f, 0.0f, -50.0f }, { 1.0f, 1.0f, 1.f });

	vertexProcessor.update();

	auto lights = std::vector<Light*>{
		 new PointLight{ {0.0f, 0.9f, .0f}, {10.f, 10.f, 0.f}, 0.5f, 50 },
		 new DirectionalLight{{0.99f, 0.f, 0.f}, {0.f, 1.f, 0.f}, 0.8f, 5}

		 //new PointLight{ {0.9f, 0.0f, .0f}, {0.f, 0.f, -5.f}, 0.4f, 10 },
		 //new PointLight{ {0.0f, 0.0f, .9f}, {20.f, 0.f, 0.f}, 0.4f, 50 }
	};

	drawModel(imageBuffer,
		vertexProcessor,
		{ -10.f, 0.f, 0.f }, //pos
		{ 10.f, 10.f, 10.f }, //scale
		{ 0.f, 1.f, 0.f }, //rotAxis
		90.f, //angle
		sphere,
		lights);

	drawModel(imageBuffer,
		vertexProcessor,
		{ 10.f, -5.f, 0.f },
		{ 1.f, 1.f, 1.f },
		{ 0.f, 1.f, 0.f },
		-90.f,
		kettle,
		lights);

	auto timerEnd = Clock::now();
	auto time = std::chrono::duration_cast<duration>(timerEnd - timerStart);

	std::cout << "Rendered in: " << time.count();
	TGASaver::toPPM("lamared", imageBuffer.getColors(), imageBuffer.getWidth(), imageBuffer.getHeigth());
	//std::cin.get();
	return 0;
}

