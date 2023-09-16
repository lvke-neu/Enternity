#pragma once
#include "../Node.h"
#include "Transform3D.h"

namespace Enternity
{
	class Node3D : public Node
	{
		RTTR_ENABLE(Node);
	public:
		Node3D();
	public:
		GET_CLASS_NAME(Node3D);
	public:
		GET_SET(Transform3D, transform);
	public:
		Transform3D& getTransform()
		{
			return m_transform;
		}
	private:
		Transform3D m_transform;
	};
}