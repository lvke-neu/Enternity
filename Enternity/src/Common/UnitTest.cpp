#include "Engine/Engine.h"
#include "Engine/Blob.h"
#include "Engine/BlobLoader.h"
#include "Engine/BlobHolder.h"
#include "Engine/BlobLoaderManager.h"
#include "Engine/Log.h"

using namespace Enternity;

int main(int argc, const char** argv) {

	Enternity::Engine::GetInstance().initialize();

	std::string path = "file://assets/shaders/test/test2.frag";
	BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path);
	BlobHolder* blobHolder = nullptr;
	if (blobLoader)
	{
		blobHolder = blobLoader->createBlobHolder(path);
		blobHolder->load();
	}

	while (true)
	{
		if (blobHolder->isLoadSucceeded())
		{
			std::string str((char*)blobHolder->getBlob()->getData(), blobHolder->getBlob()->getLength());
			int i = 0;
			i++;
		}
	}
	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();

	return 0;
}


