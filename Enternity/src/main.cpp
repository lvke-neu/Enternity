#include "Engine/Engine.h"
#include "Function/Render/Wrapper/RenderWrapper.h"
#include "Core/File/Blob.h"

using namespace Enternity;
void UnitTest()
{
	VertexBufferLayout vbl;
	VertexBuffer* vtb = RenderWrapper::Create<VertexBuffer>();
	Blob* blob = new Blob(1024);
	vtb->setData(blob, vbl);
	RenderWrapper::Destroy(vtb);
	SAFE_DELETE_SET_NULL(blob);
}

int main()
{
	Enternity::Engine::GetInstance().initialize();
	//TODO:remove
	UnitTest();

	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();

	return 0;
}