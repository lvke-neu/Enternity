#include "Reference.h"
#include "Common/Utility.h"

namespace Enternity
{
	Reference::Reference()
	{
		m_uuid = Utility::GenerateUUID();
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Reference>("Reference")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			);
	}
}