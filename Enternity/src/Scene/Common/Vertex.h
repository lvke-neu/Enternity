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

	struct VertexPosColorNormalTexcoord
	{
		Vector3f position;
		Vector3f color;
		Vector3f normal;
		Vector2f texcoord;

		static VertexBufferLayout vertexBufferLayout;
	};

	struct VertexPosNormalTexcoord
	{
		Vector3f position;
		Vector3f normal;
		Vector2f texcoord;
		static VertexBufferLayout vertexBufferLayout;
	};
}