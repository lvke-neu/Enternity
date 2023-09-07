#pragma once
#include "Node.h"
#include "Transform3D.h"
#include "Common/Macro.h"

namespace Enternity
{
	class Node3D : public Node
	{
	public:
		GET_SET(Transform3D, transform);
	private:
		Transform3D m_transform;
	};
}