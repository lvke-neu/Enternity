#pragma once
#include "../Component.h"

namespace Enternity
{
	class Mesh;
	class Renderer;
	class TextureCubeMapHDR;
	class TextureCubeMap;
	class SkyBoxComponent : public Component
	{
	public:
		enum class Type
		{
			HDR,
			Image
		};

		RTTR_ENABLE(Component);
	public:
		SkyBoxComponent();
		~SkyBoxComponent();
	public:
		GET_CLASS_NAME(SkyBoxComponent);
	public:
		GET_SET(std::string, meshPath);
		GET_SET(std::string, rendererPath);
		GET_SET(std::string, textureCubeMapHDRPath);
		GET_SET(std::string, textureCubeMapPath);
		GET_SET(Type, skyboxType);
	public:
		virtual void tick() override;
	private:
		std::string m_meshPath;
		std::string m_rendererPath;
		std::string m_textureCubeMapHDRPath;
		std::string m_textureCubeMapPath;

		Mesh* m_mesh;
		Renderer* m_renderer;
		TextureCubeMapHDR* m_textureCubeMapHDR;
		TextureCubeMap* m_textureCubeMap;

		Type m_skyboxType;
	};
}