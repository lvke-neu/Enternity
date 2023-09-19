#pragma once
#include "Engine/Component.h"
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
		GET(float, fovy);
		GET(float, aspect);
		GET(float, nearz);
		GET(float, farz);

		void set_fovy(float fovy);
		void set_aspect(float aspect);
		void set_nearz(float nearz);
		void set_farz(float farz);
	public:
		virtual void command();
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