#include "Engine/Engine.h"
#include "Engine/BlobLoader.h"
#include "Engine/BlobHolder.h"
#include "Engine/BlobLoaderManager.h"

using namespace Enternity;

int main(int argc, const char** argv) {

	Enternity::Engine::GetInstance().initialize();

	BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader("file://asdad");

	if (blobLoader)
	{
		BlobHolder* blobHolder = blobLoader->createBlobHolder("file://asdad");
		blobHolder->load();
	}


	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();

	return 0;
}


