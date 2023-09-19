#include "Camera3DComponent.h"
#include "Node3D.h"
#include "Engine/Engine.h"
#include "Engine/EventSystem.h"
#include "Graphics/RHI/UniformBuffer/UniformBuffer.h"
#include <rttr/registration>
#include <glm/gtc/type_ptr.hpp>

namespace Enternity
{
	Camera3DComponent::Camera3DComponent() :
		m_fovy(60.0f),
		m_aspect(1.0f),
		m_nearz(1.0f),
		m_farz(1000.0f)
	{
		m_uniformBufferProjection = new UniformBuffer;
		m_uniformBufferView = new UniformBuffer;

		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::WindowResize, BIND(Camera3DComponent::onWindowResize));
	}

	Camera3DComponent::~Camera3DComponent()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::WindowResize, BIND(Camera3DComponent::onWindowResize));
		SAFE_DELETE_SET_NULL(m_uniformBufferProjection);
		SAFE_DELETE_SET_NULL(m_uniformBufferView);
	}

	void Camera3DComponent::command()
	{
		//projection matrix
		auto view = getNode<Node3D>()->getTransform().getInverseWorldMatrix();
		m_uniformBufferView->modify(glm::value_ptr(view), sizeof(glm::mat4), 1);
	}

	void Camera3DComponent::onWindowResize(void* data)
	{
		WindowSize ws = *(WindowSize*)(data);
		m_aspect = static_cast<float>(ws.width) / ws.height;

		//view matrix
		auto proj = getProjectionMatrix();
		m_uniformBufferProjection->modify(glm::value_ptr(proj), sizeof(glm::mat4), 0);
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Camera3DComponent>("Camera3DComponent")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("fovy", &Camera3DComponent::get_fovy, &Camera3DComponent::set_fovy)
			.property("aspect", &Camera3DComponent::get_aspect, &Camera3DComponent::set_aspect)
			.property("nearz", &Camera3DComponent::get_nearz, &Camera3DComponent::set_nearz)
			.property("farz", &Camera3DComponent::get_farz, &Camera3DComponent::set_farz);
	}
}