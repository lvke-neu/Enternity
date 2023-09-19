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
		GET_SET(bool, wireFrame);
		GET_SET(Material*, material);
		void setMesh(Mesh* mesh);
		void setRenderer(Renderer* renderer);
		void setMaterial(Material* material);
	public:
		virtual void command() override;
	protected:
		bool m_wireFrame;

		Mesh* m_mesh;
		Renderer* m_renderer;
		Material* m_material;
	};
}