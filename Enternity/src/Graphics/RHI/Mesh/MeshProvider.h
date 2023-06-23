#pragma once
#include <functional>
#include <unordered_map>

namespace Enternity
{
	class Mesh;
	class MeshAsset;
	class MeshProvider
	{
		struct MeshAsset_Callback
		{
			MeshAsset* meshAsset;
			std::function<void(void)> callback;
		};
	public:
		MeshProvider();
		~MeshProvider();
	public:
		Mesh* getMeshSync(const char* fullPath);
		void  getMeshAsyn(Mesh** mesh, const char* fullPath, std::function<void(void)> callback);
	private:
		void tick(void* data);
	private:
		std::unordered_map<Mesh**, MeshAsset_Callback> m_map;
	};
}