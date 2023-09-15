#pragma once
#include "Common/Macro.h"
#include <string>
#include <rttr/registration>

namespace Enternity
{
	class Reference
	{
		RTTR_ENABLE();
	public:
		Reference();
		virtual ~Reference() = default;
	public:
		GET_CLASS_NAME(Reference);
	public:
		GET(std::string, uuid);
	protected:
		std::string m_uuid;
	};
}