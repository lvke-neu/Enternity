#pragma once
#include "Engine/Reference.h"
#include <memory>

namespace Enternity 
{
	class Node3D;
	class Mesh;
	class Renderer;
	class Material;
	class Visual3D : public Reference
	{
		RTTR_ENABLE(Reference);
	public:
		Visual3D();
	public:
		GET_CLASS_NAME(Visual3D);
	public:
		GET_SET(bool, enable);
		GET_SET(bool, wireFrame);
		GET_SET(std::string, name);
		GET(std::shared_ptr<Mesh>, mesh);
		GET(std::shared_ptr<Renderer>, renderer);
		GET(std::shared_ptr<Material>, material);
		SET(Node3D*, node);
		void set_mesh(std::shared_ptr<Mesh> mesh);
		void set_renderer(std::shared_ptr<Renderer> renderer);
		void set_material(std::shared_ptr<Material> material);
	public:
		void draw();
	private:
		std::shared_ptr<Mesh> m_mesh;
		std::shared_ptr<Renderer> m_renderer;
		std::shared_ptr<Material> m_material;
		Node3D* m_node;
		std::string m_name;
		bool m_enable;
		bool m_wireFrame;
	};
}