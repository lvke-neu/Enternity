#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix4x4.h"

namespace Enternity
{
	struct TransformComponent
	{
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;

		Vector3f m_position = Vector3f::ZERO;
		Vector3f m_rotation = Vector3f::ZERO;
		Vector3f m_scale = Vector3f::ONE;

		Matrix4x4f getWorldMatrix()
		{
			return Matrix4x4f::Translate(m_position.x, m_position.y, m_position.z) *
				Matrix4x4f::Rotate(m_rotation.x, m_rotation.y, m_rotation.z)*
				Matrix4x4f::Scale(m_scale.x, m_scale.y, m_scale.z);
		}
	};

}