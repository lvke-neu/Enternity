#pragma once
#include "../Component.h"

namespace Enternity
{
	class Mesh;
	class Renderer;
	class TextureCubeMapHDR;
	class HDRSkyBoxComponent : public Component
	{
		RTTR_ENABLE(Component);
	public:
		HDRSkyBoxComponent();
		~HDRSkyBoxComponent();
	public:
		GET_CLASS_NAME(HDRSkyBoxComponent);
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
		TextureCubeMapHDR* m_texture;
	};
}