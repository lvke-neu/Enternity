#pragma once
#include "Core/Math/Vector.h"
#include "RHI/VertexBufferLayout.h"

namespace Enternity
{
	struct VertexPosColor
	{
		Vector3f position;
		Vector3f color;

		static VertexBufferLayout vertexBufferLayout;
	};

}