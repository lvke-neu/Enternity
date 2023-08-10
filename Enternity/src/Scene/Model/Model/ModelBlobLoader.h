#pragma once
#include "Engine/BlobLoader.h"

struct aiNode;
struct aiScene;
struct aiMesh;

namespace Enternity
{
	class MeshBlobHolder;
	class ModelBlobLoader : public BlobLoader
	{
	public:
		ModelBlobLoader();
	public:
		virtual BlobHolder* createBlobHolder(const char* path);
		virtual void doLoad(BlobHolder* blobHolder) override;
	private:
		void processNode(BlobHolder* blobHolder, aiNode* node, const aiScene* scene);
		MeshBlobHolder* processMesh(aiMesh* mesh, const aiScene* scene);
	};
}