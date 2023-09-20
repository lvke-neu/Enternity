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
		GET(Mesh*, mesh);
		GET(Renderer*, renderer);
		GET(Material*, material);
		void set_mesh(Mesh* mesh);
		void set_renderer(Renderer* renderer);
		void set_material(Material* material);
	public:
		virtual void command() override;
	protected:
		Mesh* m_mesh;
		Renderer* m_renderer;
		Material* m_material;
	};
}