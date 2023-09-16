#pragma once
#include "../Component.h"

namespace Enternity
{
	class Mesh;
	class Renderer;
	class Texture2D;
	class Visual3DComponent : public Component
	{
		RTTR_ENABLE(Component);
	public:
		Visual3DComponent();
		~Visual3DComponent();
	public:
		GET_CLASS_NAME(Visual3DComponent);
	public:
		GET_SET(std::string, meshPath);
		GET_SET(std::string, rendererPath);
		GET_SET(std::string, texturePath);
	public:
		virtual void tick() override;
	private:
		std::string m_meshPath;
		std::string m_rendererPath;
		std::string m_texturePath;

		Mesh* m_mesh;
		Renderer* m_renderer;
		Texture2D* m_texture;
	};
}