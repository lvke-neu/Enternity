#pragma once
#include "../Component.h"
#include <rttr/registration>

namespace Enternity
{
	enum class Color
	{
		Red,
		Green,
		Blue
	};

	enum class Postprocess
	{
		Gray,
		Blur
	};

	class Visual3DComponent : public Component
	{
		RTTR_ENABLE(Component);
	public:
		Visual3DComponent();
		~Visual3DComponent();
	public:
		GET_CLASS_NAME(Visual3DComponent);
	public:
		GET_SET(std::string, texture);
		GET_SET(std::string, renderer);
		GET_SET(Color, color);
		GET_SET(Postprocess, postprocess);
	private:
		std::string m_texture;
		std::string m_renderer;
		Color m_color;
		Postprocess m_postprocess;
	};


}