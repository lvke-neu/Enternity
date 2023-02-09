#include "Engine/Engine.h"


//**********************************UnitTest********************************************
#include "Function/Render/Wrapper/RenderWrapper.h"
#include "Core/File/Blob.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector2.h"
#include "Core/Timer/ExecutionTimer.h"
#include <glad/glad.h>
using namespace Enternity;



void UnitTest()
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

	RenderWrapper::Destroy(vtb);
	SAFE_DELETE_SET_NULL(blob);

	RenderWrapper::Destroy(vta);
}
//**********************************************************************************


int main()
{
	Enternity::Engine::GetInstance().initialize();
	//TODO:remove
	UnitTest();

	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();

	return 0;
}