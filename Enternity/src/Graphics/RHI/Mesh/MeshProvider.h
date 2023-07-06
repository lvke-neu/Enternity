#pragma once
#include <functional>
#include <vector>

namespace Enternity
{
	class Mesh;
	class MeshAsset;
	class MeshProvider
	{
	public:
		enum BasicPrimitve
		{
			Quad,
			Box
		};
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
		Mesh* getMeshSync(BasicPrimitve type);
		void  getMeshAsyn(const char* fullPath, std::function<void(Mesh*)> callback);
		void  getMeshAsyn(BasicPrimitve type, std::function<void(Mesh*)> callback);
	private:
		void tick(void* data);
	private:
		std::vector <MeshAsset_Callback > m_map;
	};
}