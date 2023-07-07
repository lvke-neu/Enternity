#pragma once
#include "MeshDefine.h"
#include <functional>
#include <vector>

namespace Enternity
{
	class Mesh;
	class MeshAsset;
	class MeshProvider
	{
	public:
		struct MeshAsset_Callback
		{
			MeshAsset* meshAsset;
			std::function<void(Mesh*)> callback;
		};
	public:
		MeshProvider();
		~MeshProvider();
	public:
		Mesh* getMeshSync(const char* fullPath);
		Mesh* getMeshSync(BasicMeshType type, const std::string& texturePath = "");
		void  getMeshAsyn(const char* fullPath, std::function<void(Mesh*)> callback);
		void  getMeshAsyn(BasicMeshType type, std::function<void(Mesh*)> callback, const std::string& texturePath = "");
	private:
		void tick(void* data);
	private:
		std::vector <MeshAsset_Callback > m_map;
	};
}