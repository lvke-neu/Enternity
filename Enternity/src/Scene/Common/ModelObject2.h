#pragma once
#include "Transform.h"
#include "Material.h"
#include <vector>
#include <string>

struct aiNode;
struct aiMesh;
struct aiScene;
namespace Enternity
{

	class Camera3D;
	class Light;
	class VertexArray;
	class IndexBuffer;
	class Shader;
	class ModelObject2
	{

	public:
		ModelObject2(Camera3D* camera3D, Light* light);
		~ModelObject2();
		void Load(const std::string& path);
		void Draw();
		void RenderGUI();
	private:
		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);
	public:
		Transform m_transform{ {0.0f, -2.0f, 0.0f}, {0.0f, 0.0f, 0.0f},{0.3f, 0.3f, 0.3f} };
	private:
		Camera3D* m_pCamera3D;
		Light* m_pLight;	
	private:
		std::vector<VertexArray*> m_pVertexArraies;
		std::vector<IndexBuffer*> m_pIndexBuffers;
		std::vector<Shader*> m_pShaders;
		std::vector<PhongMaterial> m_materials;

		bool m_bIsLoad = false;
		std::string m_modelFilePath;
	};
}