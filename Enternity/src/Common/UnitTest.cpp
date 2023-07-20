//#include "Engine/Engine.h"
//#include "Engine/Blob.h"
//#include "Engine/BlobLoader.h"
//#include "Engine/BlobHolder.h"
//#include "Engine/BlobLoaderManager.h"
//#include "Engine/Log.h"
//#include "Engine/Detail/texture/TextureBlobHolder.h"
//#include "Engine/Detail/mesh/MeshBlobHolder.h"
//#include <glm/glm.hpp>
//
//using namespace Enternity;
//
//int main(int argc, const char** argv) {
//
//	Enternity::Engine::GetInstance().initialize();
//
//	//std::string path = "renderer://assets/shaders/test/test2.frag";
//	//BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path);
//
//	//if (blobLoader)
//	//{
//	//	BlobHolder* blobHolder = blobLoader->createBlobHolder(path);
//	//	blobHolder->load();
//	//	while (!blobHolder->isLoadSucceeded())
//	//	{
//	//		
//	//	}
//	//}
//
//	//std::string path = "texture://assets/textures/atmosphere.png";
//	//BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path);
//
//	//
//
//	//if (blobLoader)
//	//{
//	//	BlobHolder* blobHolder = blobLoader->createBlobHolder(path);
//	//	blobHolder->load();
//	//	while (!blobHolder->isLoadSucceeded())
//	//	{
//	//		
//	//	}
//	//}
//
//	std::string path = "mesh://assets/models/nanosuit/nanosuit.obj";
//	BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path);
//
//	if (blobLoader)
//	{
//		BlobHolder* blobHolder = blobLoader->createBlobHolder(path);
//		blobHolder->load();
//		while (!blobHolder->isLoadSucceeded())
//		{
//			
//		}
//
//		MeshBlobHolder* meshBlobHolder = dynamic_cast<MeshBlobHolder*>(blobHolder);
//
//		int i = 0;
//		i++;
//	}
//
//
//	Enternity::Engine::GetInstance().run();
//	Enternity::Engine::GetInstance().uninitialize();
//
//	return 0;
//}
//
//
