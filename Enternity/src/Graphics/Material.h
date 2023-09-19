//wrapper texture2d
#pragma once
#include "Engine/Reference.h"
#include "Color.h"

namespace Enternity
{
	class Material : public Reference
	{
		RTTR_ENABLE(Reference);
	public:
		GET_CLASS_NAME(Material);
	public:
		GET_SET(Color, ambientColor);
		GET_SET(Color, diffuseColor);
		GET_SET(Color, specularColor);
	private:
		Color m_ambientColor;
		Color m_diffuseColor;
		Color m_specularColor;
	};
}