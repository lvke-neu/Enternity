#pragma once
#include "../Component.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Enternity
{
	class UniformBuffer;
	class Camera3DComponent : public Component
	{
		RTTR_ENABLE(Component);
	public:
		Camera3DComponent();
		~Camera3DComponent();
	public:
		GET_CLASS_NAME(Camera3DComponent);
	public:
		GET_SET(float, fovy);
		GET_SET(float, aspect);
		GET_SET(float, nearz);
		GET_SET(float, farz);
	public:
		virtual void tick();
		glm::mat4 getProjectionMatrix()
		{
			return glm::perspective<float>(glm::radians(m_fovy), m_aspect, m_nearz, m_farz);
		}
	private:
		void onWindowResize(void* data);
	private:
		float m_fovy;
		float m_aspect;
		float m_nearz;
		float m_farz;

		UniformBuffer* m_uniformBufferProjection;
		UniformBuffer* m_uniformBufferView;

	};
}