#pragma once
#include <string>

namespace Enternity
{
	struct TagComponent
	{
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;

		std::string m_Tag{ "undefined" };
	};
}