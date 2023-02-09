#include "Engine/Engine.h"
#include "Function/Render/Wrapper/RenderWrapper.h"
#include "Core/File/Blob.h"

using namespace Enternity;
void UnitTest()
{
	VertexBuffer* vtb = RenderWrapper::Create<VertexBuffer>();
	Blob* blob = Blob::New(1024);
	vtb->setData(blob);
	RenderWrapper::Destroy(vtb);
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