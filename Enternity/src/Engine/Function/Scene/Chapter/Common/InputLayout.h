#pragma once
#include "Core/Math/Vector3.h"
#include "Function/Render/Wrapper/VertexBuffer.h"
#include <glad/glad.h>

namespace Enternity
{
	struct InputLayout
	{
		static void Init();
		static VertexBufferLayout VertexBufferLayout_POS_COLOR;
	private:
		static bool bInit;
	};
}