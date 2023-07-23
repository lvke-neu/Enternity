#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Engine/BlobLoaderManager.h"
#include "Engine/BlobLoader.h"
#include "Engine/BlobHolder.h"
#include "Graphics/RHI/Mesh/MeshBlobHolder.h"
#include "Graphics/RHI/Mesh/VertexDefine.h"
#include "Graphics/RHI/Mesh/MeshBlobLoader.h"
#include "Engine/Blob.h"
#include <glm/glm.hpp>

using namespace Enternity;

int main(int argc, const char** argv) {

	Enternity::Engine::GetInstance().initialize();

	std::string path = "mesh://primitive=cube";
	BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path.c_str());

	if (blobLoader)
	{
		MeshBlobHolder* meshBlobHolder = dynamic_cast<MeshBlobHolder*>(blobLoader->createBlobHolder(path.c_str()));

		if (meshBlobHolder)
		{
			meshBlobHolder->load();
			while (!meshBlobHolder->isLoadSucceeded())
			{

			}
			std::vector<Vertex_Positon_Normal_Texcoord> vertices;
			vertices.resize(24);
			std::vector<unsigned int> indices;
			indices.resize(36);
			memcpy_s(vertices.data(), meshBlobHolder->getMeshDesc().vertexDataSize,
				(char*)meshBlobHolder->getBlob()->getData() + meshBlobHolder->getMeshDesc().vertexDataOffset,
				meshBlobHolder->getMeshDesc().vertexDataSize);
			memcpy_s(indices.data(), meshBlobHolder->getMeshDesc().indexDataSize,
				(char*)meshBlobHolder->getBlob()->getData() + meshBlobHolder->getMeshDesc().indexDataOffset,
				meshBlobHolder->getMeshDesc().indexDataSize);
			int i = 0;
			i++;
		}
	}

	//std::string path = "renderer://assets/shaders/test/test2.rdr";
	//Engine::GetInstance().getAssetLoader()->getAsset(path.c_str(),
	//	[=](Asset* asset)
	//	{
	//		Renderer* rdr = dynamic_cast<Renderer*>(asset);
	//		if (rdr && rdr->isLoadSucceeded())
	//		{
	//			rdr->bind();
	//		}

	//		int i = 0;
	//		i++;
	//	});

	//path = "texture://assets/textures/atmosphere.png";
	//auto asset = Engine::GetInstance().getAssetLoader()->getAsset(path.c_str());
	//int i = 0;
	//i++;



	//std::string path = "renderer://assets/shaders/test/test2.rdr";

	//Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRHIAsset(path.c_str(),
	//	[=](RHIAsset* rhiAsset)
	//	{
	//		Renderer* rdr = dynamic_cast<Renderer*>(rhiAsset);
	//		if (rdr && rdr->isLoadSucceeded())
	//		{
	//			rdr->bind();
	//		}
	//		
	//		int i = 0;
	//		i++;
	//	});

	//path = "renderer://assets/textures/atmosphere.png";
	//Engine::GetInstance()


	//BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path);

	//if (blobLoader)
	//{
	//	BlobHolder* blobHolder = blobLoader->createBlobHolder(path);
	//	blobHolder->load();
	//	while (!blobHolder->isLoadSucceeded())
	//	{
	//		
	//	}

	//	RendererBlobHolder* rendererBlobHolder = (RendererBlobHolder*)blobHolder;

	//	std::string vs((char*)rendererBlobHolder->getBlob()->getData() + rendererBlobHolder->getShaderDesc().vertDataOffset,
	//		rendererBlobHolder->getShaderDesc().vertDataSize);

	//	std::string gs((char*)rendererBlobHolder->getBlob()->getData() + rendererBlobHolder->getShaderDesc().geomDataOffset,
	//		rendererBlobHolder->getShaderDesc().geomDataSize);

	//	std::string ps((char*)rendererBlobHolder->getBlob()->getData() + rendererBlobHolder->getShaderDesc().fragDataOffset,
	//		rendererBlobHolder->getShaderDesc().fragDataSize);

	//	int i = 0;
	//	i++;
	//}

	//std::string path = "texture://assets/textures/atmosphere.png";
	//BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path);

	//

	//if (blobLoader)
	//{
	//	BlobHolder* blobHolder = blobLoader->createBlobHolder(path);
	//	blobHolder->load();
	//	while (!blobHolder->isLoadSucceeded())
	//	{
	//		
	//	}
	//}

	//std::string path = "mesh://assets/models/nanosuit/nanosuit.obj";
	//BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path);

	//if (blobLoader)
	//{
	//	BlobHolder* blobHolder = blobLoader->createBlobHolder(path);
	//	blobHolder->load();
	//	while (!blobHolder->isLoadSucceeded())
	//	{
	//		
	//	}

	//	MeshBlobHolder* meshBlobHolder = dynamic_cast<MeshBlobHolder*>(blobHolder);

	//	int i = 0;
	//	i++;
	//}



	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();

	return 0;
}


