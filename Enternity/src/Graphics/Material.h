//wrapper texture2d
#pragma once
#include "Engine/Reference.h"
#include "Color.h"

namespace Enternity
{
	class Renderer;
	class Texture2D;
	class Material : public Reference
	{
		RTTR_ENABLE(Reference);
	public:
		Material();
		~Material();
	public:
		GET_CLASS_NAME(Material);
	public:
		GET_SET(Color, ambientColor);
		GET_SET(Color, diffuseColor);
		GET_SET(Color, specularColor);
		GET_SET(std::string, ambientTexturePath);
		GET_SET(std::string, diffuseTexturePath);
		GET_SET(std::string, specularTexturePath);

		GET(Texture2D*, ambientTexture);
		GET(Texture2D*, diffuseTexture);
		GET(Texture2D*, specularTexture);
	public:
		void load();
		void bind(Renderer* renderer);
		void unbind();
	private:
		Color m_ambientColor;
		Color m_diffuseColor;
		Color m_specularColor;

		std::string m_ambientTexturePath;
		std::string m_diffuseTexturePath;
		std::string m_specularTexturePath;

		Texture2D* m_ambientTexture;
		Texture2D* m_diffuseTexture;
		Texture2D* m_specularTexture;
	};
}