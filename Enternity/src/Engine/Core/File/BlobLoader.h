/***************************************************************************************
Author: lvke
Date:2023/2/5 22:50
Description:
BlobLoader
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"
#include <string>

namespace Enternity
{
	enum class LoadType
	{
		Sync,
		Asyn
	};

	class Blob;
	class BlobLoader
	{
	public:
		void loadGeneral(Blob*& blob, const std::string& filePath, LoadType loadType);
		void loadTexture(Blob*& blob, const std::string& filePath, LoadType loadType, int desired_channels = 0);
		void loadMesh(Blob*& verticesBlob, Blob*& indicesBlob, const std::string& filePath, LoadType loadType);
	private:
		void loadGeneralImpl(Blob*& blob, const std::string& filePath);
		void loadTextureImpl(Blob*& blob, const std::string& filePath);
		void loadMeshImpl(Blob*& verticesBlob, Blob*& indicesBlob, const std::string& filePath);
	};
}