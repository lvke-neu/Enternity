#pragma once
#include "Engine/Component.h"

namespace Enternity
{
	class Mesh;
	class Renderer;
	class Material;
	class Visual3DComponent : public Component
	{
		RTTR_ENABLE(Component);
	public:
		Visual3DComponent();
		virtual ~Visual3DComponent();
	public:
		GET_CLASS_NAME(Visual3DComponent);
	public:
		GET_SET(std::string, meshPath);
		GET_SET(std::string, rendererPath);
		GET_SET(bool, wireFrame);
		GET_SET(Material*, material);
	public:
		virtual void command() override;
	protected:
		std::string m_meshPath;
		std::string m_rendererPath;
		bool m_wireFrame;
		Material* m_material;

		Mesh* m_mesh;
		Renderer* m_renderer;
	};
}