#pragma once
#include "Engine/BlobLoader.h"

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;
namespace Enternity
{
	class MeshBlobHolder;
	class Texture2DBlobHolder;
	class ModelBlobLoader : public BlobLoader
	{
	public:
		ModelBlobLoader();
	public:
		virtual BlobHolder* createBlobHolder(const char* path);
		virtual void doLoad(BlobHolder* blobHolder) override;
	private:
		void processNode(BlobHolder* blobHolder, aiNode* node, const aiScene* scene);
		MeshBlobHolder* processMesh(BlobHolder* blobHolder, aiMesh* mesh, const aiScene* scene);
		Texture2DBlobHolder* processMaterial(const std::string& path, aiMaterial* material);
	};
}