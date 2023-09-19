#pragma once
#include "Engine/Component.h"

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
		virtual ~Visual3DComponent();
	public:
		GET_CLASS_NAME(Visual3DComponent);
	public:
		GET_SET(std::string, meshPath);
		GET_SET(std::string, rendererPath);
		GET_SET(std::string, texturePath);
		GET_SET(bool, wireFrame);
	public:
		virtual void command() override;
	protected:
		std::string m_meshPath;
		std::string m_rendererPath;
		std::string m_texturePath;
		bool m_wireFrame;

		Mesh* m_mesh;
		Renderer* m_renderer;
		Texture2D* m_texture;
	};
}