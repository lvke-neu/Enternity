//#pragma once
//
//**********************************UnitTest********************************************
//#include "Function/Render/Wrapper/RenderWrapper.h"
//#include "Function/Render/RenderSystem.h"
//#include "Core/File/Blob.h"
//#include "Core/File/BlobLoader.h"
//#include "Core/Math/Vector4.h"
//#include "Core/Math/Vector3.h"
//#include "Core/Math/Vector2.h"
//#include "Core/Timer/ExecutionTimer.h"
//#include "Core/Basic/UUID.h"
//#include "Function/Scene/Scene.h"
//#include "Core/Math/Math.h"
//#include <glad/glad.h>
//using namespace Enternity;
//
//
//
//
//#include "Core/ThreadPool/ThreadPool.h"
//
//typedef void(*notify)(std::vector<Blob*>& datas);
//
//std::vector<Blob*> textures;
//std::mutex mtx;
//void loadTexture(notify func)
//{
//	BlobLoader blobLoader;
//	mtx.lock();
//	textures.emplace_back(blobLoader.load("assets/textures/box_diffuse.png", AssetType::Texture));
//	if (textures.size() == 100)
//		func(textures);
//	mtx.unlock();
//}
//
//ThreadPool threadPool(8);
//void testThreadPool(notify func)
//{
//	for (int i = 0; i < 100; i++)
//	{
//		threadPool.commitTask(std::bind(loadTexture, func));
//	}
//}
//
//
//
//void UnitTest(notify func)
//{
//	
//	ExecutionTimer executionTimer("The time of UnitTest");
//	struct VertexPosNormalTex
//	{
//		Vector3f position;
//		Vector3f normal;
//		Vector2f texcoord;
//	};
//
//	vertices
//	std::vector<VertexPosNormalTex> vertices;
//	vertices.resize(24);
//	for (int i = 0; i < vertices.size(); i++)
//	{
//		vertices[i].position = Vector3f::ONE;
//		vertices[i].normal = Vector3f::ONE;
//		vertices[i].texcoord = Vector2f::ONE;
//	}
//
//	vertices blob
//	Blob* blob = new Blob((unsigned int)vertices.size() * sizeof(VertexPosNormalTex));
//	memcpy_s(blob->getData(), blob->getLength(), vertices.data(), blob->getLength());
//
//	layout
//	VertexBufferLayout vertexBufferLayout;
//	vertexBufferLayout.push({ 0, 3, GL_FLOAT, false,  8 * sizeof(float), 0 });
//	vertexBufferLayout.push({ 1, 3, GL_FLOAT, false,  8 * sizeof(float), 3 * sizeof(float) });
//	vertexBufferLayout.push({ 2, 2, GL_FLOAT, false,  8 * sizeof(float), 6 * sizeof(float) });
//
//	vertexbuffer
//	VertexBuffer* vtb = RenderWrapper::Create<VertexBuffer>();
//	vtb->init(blob, vertexBufferLayout);
//
//	vertexarray
//	VertexArray* vta = RenderWrapper::Create<VertexArray>();
//	vta->init(vtb);
//
//
//	indexbuffer;
//	std::vector<unsigned int> indices;
//	indices.resize(36);
//	for (int i = 0; i < indices.size(); i++)
//	{
//		indices[i] = 1;
//	}
//
//	Blob* blob2 = new Blob(indices.size() * sizeof(unsigned int));
//	memcpy_s(blob2->getData(), blob2->getLength(), indices.data(), blob2->getLength());
//
//	IndexBuffer* ib = RenderWrapper::Create<IndexBuffer>();
//	ib->init(blob2);
//
//	RenderWrapper::Destroy(vtb);
//	SAFE_DELETE_SET_NULL(blob);
//	SAFE_DELETE_SET_NULL(blob2);
//
//	RenderWrapper::Destroy(vta);
//	RenderWrapper::Destroy(ib);
//
//
//	test blob general loader
//	Blob* blob3;
//	BlobLoader blobLoader;
//	blob3 = blobLoader.load("assets/shaders/TestECSPhong.glsl", AssetType::General);
//	std::string logcontent((char*)blob3->getData(), blob3->getLength());
//	SAFE_DELETE_SET_NULL(blob3);
//
//	test blob texture loader
//	testThreadPool(func);
//
//	Texture2D* texture2d = RenderWrapper::Create<Texture2D>();
//	Blob* blob4;
//	blob4 = blobLoader.load("assets/textures/skybox.jpeg", AssetType::Texture);
//	texture2d->init(blob4);
//	RenderWrapper::Destroy(texture2d);
//	SAFE_DELETE_SET_NULL(blob4);
//
//	test shader
//	Shader* shader = RenderWrapper::Create<Shader>();
//	Blob* vsBlob = blobLoader.load("assets/shaders/Phong.vert", AssetType::General);
//	std::string vsstr((char*)vsBlob->getData());
//	Blob* psBlob = blobLoader.load("assets/shaders/Phong.frag", AssetType::General);
//	std::string psstr((char*)psBlob->getData());
//	shader->init(vsBlob, psBlob);
//
//	test scene
//	Scene scene;
//	std::string str;
//	for (int i = 0; i < 100; i++)
//	{
//		str = scene.createEntity();
//	}
//	scene.deleteEntity("13jdsauge-3232233-4e223n");
//	scene.deleteAll();
//	int i = 0;
//	i++;
//}
//
//VertexArray* vertexArray{ nullptr };
//VertexBuffer* vertexBuffer{ nullptr };
//IndexBuffer* indexBuffer{ nullptr };
//Shader* shader{ nullptr };
//
//void TestDraw()
//{
//	if (!vertexArray)
//	{
//		Vector3f vertices[3] =
//		{
//			{-0.5, 0.0f, 0.0f},
//			{0.0f, 0.5f, 0.0f},
//			{0.5f, 0.0f, 0.0f}
//		};
//		unsigned int indices[3] = { 0,1,2 };
//
//		vertexBuffer = RenderWrapper::Create<VertexBuffer>();
//		Blob vtxBlob(3 * sizeof(Vector3f));
//		vtxBlob.copyData(vertices);
//		VertexBufferLayout vertexBufferLayout;
//		vertexBufferLayout.push({ 0, 3, GL_FLOAT, false,  3 * sizeof(float), 0 });
//		vertexBuffer->init(&vtxBlob, vertexBufferLayout);
//
//		vertexArray = RenderWrapper::Create<VertexArray>();
//		vertexArray->init(vertexBuffer);
//
//		indexBuffer = RenderWrapper::Create<IndexBuffer>();
//		Blob idxBlob(3 * sizeof(float));
//		idxBlob.copyData(indices);
//		indexBuffer->init(&idxBlob);
//
//		BlobLoader blobLoader;
//		shader = RenderWrapper::Create<Shader>();
//		Blob* vsBlob = blobLoader.load("assets/shaders/Phong.vert", AssetType::General);
//		Blob* psBlob = blobLoader.load("assets/shaders/Phong.frag", AssetType::General);
//		shader->init(vsBlob, psBlob);
//	}
//
//	vertexArray->bind();
//	indexBuffer->bind();
//	shader->bind();
//
//	test mvp matrxi
//	vertexArray->bind();
//	indexBuffer->bind();
//	shader->bind();
//	Vector3f position(0, 0, 10);
//	Vector3f rotation(0, Math::Radian(10), Math::Radian(30));
//	Matrix4x4f transMat = Matrix4x4f::Translate(position.x, position.y, position.z);
//	Matrix4x4f rotMat = Matrix4x4f::Rotate(rotation.x, rotation.y, rotation.z);
//	Matrix4x4f viewMatrix = Matrix4x4f::Inverse(transMat * rotMat);
//	Matrix4x4f projMatrix = Matrix4x4f::Perspective(PI / 6, 2, 1, 1000);
//	viewMatrix = projMatrix * viewMatrix;
//	glUniformMatrix4fv(glGetUniformLocation(shader->getRenderId(), "viewMatrix"), 1, true, viewMatrix.toData());
//	CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, (void*)0));
//	
//	//test mvp matrxi
//	vertexArray->bind();
//	indexBuffer->bind();
//	shader->bind();
//	scene->getCamera3D()->setPosition(Vector3f(0, 0, 5));
//	scene->getCamera3D()->setRotation(Vector3f(0, 360, 0));
//	Matrix4x4f viewMatrix = scene->getCamera3D()->getProjMatrix() * scene->getCamera3D()->getViewMatrix();
//	glUniformMatrix4fv(glGetUniformLocation(shader->getRenderId(), "viewMatrix"), 1, true, viewMatrix.toData());
//	CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, (void*)0));
//}
//
//**********************************************************************************
//
