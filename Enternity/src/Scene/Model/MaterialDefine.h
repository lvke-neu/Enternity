#pragma once
#include <glm/glm.hpp>
#include <string>

namespace Enternity
{
	class Texture2DBlobHolder;
	struct MaterialProperty
	{
		glm::vec4 m_ambientColor{ 1.0f };
		glm::vec4 m_diffuseColor{ 1.0f };
		glm::vec4 m_specularColor{ 1.0f };
		Texture2DBlobHolder* m_ambientTextureBlobHolder{ nullptr };
		Texture2DBlobHolder* m_diffuseTextureBlobHolder{ nullptr };
		Texture2DBlobHolder* m_specularTextureBlobHolder{ nullptr };
		std::string m_name;
	};

	class Texture2D;
	struct MaterialPropertyImpl
	{
		glm::vec4 m_ambientColor{ 1.0f };
		glm::vec4 m_diffuseColor{ 1.0f };
		glm::vec4 m_specularColor{ 1.0f };
		Texture2D* m_ambientTexture{ nullptr };
		Texture2D* m_diffuseTexture{ nullptr };
		Texture2D* m_specularTexture{ nullptr };
		std::string m_name;
	};
}