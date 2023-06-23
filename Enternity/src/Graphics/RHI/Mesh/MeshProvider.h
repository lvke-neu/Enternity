#pragma once
#include <functional>
#include <unordered_map>
#include <string>

namespace Enternity
{
	class Mesh;
	class MeshAsset;
	class MeshProvider
	{
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
		void  getMeshAsyn(const char* fullPath, std::function<void(Mesh*)> callback);
	private:
		void tick(void* data);
	private:
		std::unordered_map <std::string, MeshAsset_Callback > m_map;
	};
}