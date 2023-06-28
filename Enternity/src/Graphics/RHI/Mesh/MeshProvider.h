#pragma once
#include <functional>
#include <vector>

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

		Mesh* getQuadMesh();
	private:
		void tick(void* data);
	private:
		std::vector <MeshAsset_Callback > m_map;
	};
}