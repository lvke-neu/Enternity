#pragma once
#include "Core/Math/Vector3.h"
#include "Function/Render/Wrapper/VertexBuffer.h"
#include <glad/glad.h>

namespace Enternity
{
	struct VertexPosColor
	{
		Vector3f position;
		Vector3f color;
		static void Init();
		static VertexBufferLayout vertexBufferLayout;
	};
}