#pragma once
#include "Node.h"
#include "Transform3D.h"

namespace Enternity
{
	class Node3D : public Node
	{
	public:
		Transform3D getTransform() const;
		void setTransform(const Transform3D& transform);
	private:
		Transform3D m_transform;
	};

	inline Transform3D Node3D::getTransform() const 
	{
		return m_transform;
	}

	inline void Node3D::setTransform(const Transform3D& transform)
	{
		m_transform = transform;
	}
}