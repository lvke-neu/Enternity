#pragma once
#include <glm/glm.hpp>

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
	};
}