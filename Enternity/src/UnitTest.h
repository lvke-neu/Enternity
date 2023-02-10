//**********************************UnitTest********************************************
#include "Function/Render/Wrapper/RenderWrapper.h"
#include "Function/Render/RenderSystem.h"
#include "Core/File/Blob.h"
#include "Core/File/BlobLoader.h"
#include "Core/Math/Vector4.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector2.h"
#include "Core/Timer/ExecutionTimer.h"

#include <glad/glad.h>
using namespace Enternity;




#include "Core/ThreadPool/ThreadPool.h"

typedef void(*notify)();

std::vector<Blob*> textures;
std::mutex mtx;
void loadTexture(notify func)
{
	BlobLoader blobLoader;
	mtx.lock();
	textures.emplace_back(blobLoader.load("assets/textures/box_diffuse.png", AssetType::Texture));
	if (textures.size() == 100)
		func();
	mtx.unlock();
}

ThreadPool threadPool(8);
void testThreadPool(notify func)
{
	for (int i = 0; i < 100; i++)
	{
		threadPool.commitTask(std::bind(loadTexture, func));
	}
}



void UnitTest(notify func)
{
	
	ExecutionTimer executionTimer("The time of UnitTest");
	struct VertexPosNormalTex
	{
		Vector3f position;
		Vector3f normal;
		Vector2f texcoord;
	};

	//vertices
	std::vector<VertexPosNormalTex> vertices;
	vertices.resize(24);
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].position = Vector3f::ONE;
		vertices[i].normal = Vector3f::ONE;
		vertices[i].texcoord = Vector2f::ONE;
	}

	//vertices blob
	Blob* blob = new Blob((unsigned int)vertices.size() * sizeof(VertexPosNormalTex));
	memcpy_s(blob->getData(), blob->getLength(), vertices.data(), blob->getLength());

	//layout
	VertexBufferLayout vertexBufferLayout;
	vertexBufferLayout.push({ 0, 3, GL_FLOAT, false,  8 * sizeof(float), 0 });
	vertexBufferLayout.push({ 1, 3, GL_FLOAT, false,  8 * sizeof(float), 3 * sizeof(float) });
	vertexBufferLayout.push({ 2, 2, GL_FLOAT, false,  8 * sizeof(float), 6 * sizeof(float) });

	//vertexbuffer
	VertexBuffer* vtb = RenderWrapper::Create<VertexBuffer>();
	vtb->init(blob, vertexBufferLayout);

	//vertexarray
	VertexArray* vta = RenderWrapper::Create<VertexArray>();
	vta->init(vtb);


	//indexbuffer;
	std::vector<unsigned int> indices;
	indices.resize(36);
	for (int i = 0; i < indices.size(); i++)
	{
		indices[i] = 1;
	}

	Blob* blob2 = new Blob(indices.size() * sizeof(unsigned int));
	memcpy_s(blob2->getData(), blob2->getLength(), indices.data(), blob2->getLength());

	IndexBuffer* ib = RenderWrapper::Create<IndexBuffer>();
	ib->init(blob2);

	RenderWrapper::Destroy(vtb);
	SAFE_DELETE_SET_NULL(blob);
	SAFE_DELETE_SET_NULL(blob2);

	RenderWrapper::Destroy(vta);
	RenderWrapper::Destroy(ib);


	//test blob general loader
	Blob* blob3;
	BlobLoader blobLoader;
	blob3 = blobLoader.load("assets/shaders/TestECSPhong.glsl", AssetType::General);
	std::string logcontent((char*)blob3->getData());
	SAFE_DELETE_SET_NULL(blob3);

	//test blob texture loader
	testThreadPool(func);
}


//**********************************************************************************

