#include "Engine/Engine.h"
#include "Engine/Blob.h"
#include "Engine/BlobLoader.h"
#include "Engine/BlobHolder.h"
#include "Engine/BlobLoaderManager.h"
#include "Engine/Log.h"
#include "Engine/Detail/texture/TextureBlobHolder.h"
#include "Engine/Detail/mesh/MeshBlobHolder.h"
#include <glm/glm.hpp>

using namespace Enternity;

int main(int argc, const char** argv) {

	Enternity::Engine::GetInstance().initialize();

	//std::string path = "renderer://assets/shaders/test/test2.frag";
	//BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path);

	//if (blobLoader)
	//{
	//	BlobHolder* blobHolder = blobLoader->createBlobHolder(path);
	//	blobHolder->load();
	//	while (!blobHolder->isLoadSucceeded())
	//	{
	//		
	//	}
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

	std::string path = "mesh://assets/models/basic/Plane.fbx";
	BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path);

	if (blobLoader)
	{
		BlobHolder* blobHolder = blobLoader->createBlobHolder(path);
		blobHolder->load();
		while (!blobHolder->isLoadSucceeded())
		{
			
		}

		MeshBlobHolder* meshBlobHolder = dynamic_cast<MeshBlobHolder*>(blobHolder);

		struct Vertex_Positon_Normal_Texcoord
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 texcoord;
		};

		struct Mesh
		{
			std::vector<Vertex_Positon_Normal_Texcoord> vertices;
			std::vector<unsigned int> indices;
		};

		std::vector<Mesh> meshes;
		meshes.resize(1);
		meshes[0].vertices.resize(4);
		meshes[0].indices.resize(6);


		memcpy_s(meshes[0].vertices.data(), meshBlobHolder->getSubMeshDescs()[0].vertexDataSize, (char*)meshBlobHolder->getBlob()->getData() + meshBlobHolder->getSubMeshDescs()[0].vertexDataOffset, meshBlobHolder->getSubMeshDescs()[0].vertexDataSize);
		memcpy_s(meshes[0].indices.data(), meshBlobHolder->getSubMeshDescs()[0].indexDataSize, (char*)meshBlobHolder->getBlob()->getData() + meshBlobHolder->getSubMeshDescs()[0].indexDataOffset, meshBlobHolder->getSubMeshDescs()[0].indexDataSize);

		

		int i = 0;
		i++;
	}


	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();

	return 0;
}


