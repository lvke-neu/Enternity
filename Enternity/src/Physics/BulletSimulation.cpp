#include "BulletSimulation.h"
#include "Scene/SceneManager.h"
#include "Event/InputEventManager.h"
#include "Renderer/RenderSystem.h"
#include "Physics/PhysicsSystem.h"
#include "Imgui/ImguiManager.h"

BEGIN_ENTERNITY

BulletSimulation::BulletSimulation()
{
	//create bullet
	m_BulletEntity = Entity(SceneManager::GetInstance().GetRegistry(), "Bullet Entity");
	m_BulletEntity.AddComponent<TransformComponent>(glm::vec3{ 0 }, glm::vec3{ 0 }, glm::vec3{0.5});
	auto& matc = m_BulletEntity.AddComponent<MaterialComponent>();
	auto& meshc = m_BulletEntity.AddComponent<MeshComponent>();
	matc.m_ShaderFilePath = "assets/shaders/TestECSPhong.glsl";
	matc.m_UseTexture = false;

	meshc.m_MeshFilePath = "assets/models/sphere.mesh";
	matc.Load();
	meshc.Load();
	auto& rbc = m_BulletEntity.AddComponent<RigidBodyComponent>();
	rbc.m_ColliderShape = RigidBodyComponent::ColliderShape::Sphere;
	rbc.m_Radius = 0.5f;
	rbc.m_Friction = 0.2f;
	rbc.m_Mass = 1;
	rbc.m_Restitution = 0.9f;

	TickEventManager::GetInstance().RegisterEvent(this);
	InputEventManager::GetInstance().RegisterEvent(this);
}

void BulletSimulation::tick(float deltaTime)
{
	if (SceneManager::GetInstance().GetCurrentSceneState() == SceneState::Player)
	{
		if (m_IsLeftKeyPress)
		{
			PhysicsSystem::GetInstance().UpdateEntityState(m_BulletEntity);
			RenderSystem::GetInstance().DrawEntity(SceneManager::GetInstance().GetCurrentCameraEntity(), m_BulletEntity, SceneManager::GetInstance().GetLightEntity());
		}
	}
}

void BulletSimulation::onMousePress(MouseState mouseState)
{
	if (mouseState.mouseButton == GLFW_MOUSE_BUTTON_LEFT)
	{
		int hoverEntityId = ImguiManager::GetInstance().GetViewportPanel()->GetHoverEntityId();
		if (hoverEntityId > -1)
		{
			m_IsLeftKeyPress = true;
			auto& transc = m_BulletEntity.GetComponent<TransformComponent>();
			transc.m_Translation = SceneManager::GetInstance().GetCurrentCameraEntity().GetComponent<TransformComponent>().m_Translation;

			Entity entity(SceneManager::GetInstance().GetRegistry(), (entt::entity)hoverEntityId);
			glm::vec3 velocity = entity.GetComponent<TransformComponent>().m_Translation - transc.m_Translation;

			PhysicsSystem::GetInstance().AddEntityToPhysicsWorld(m_BulletEntity, btVector3(velocity.x, velocity.y + 5, velocity.z));
		}
	}
}

void BulletSimulation::onMouseRelease(MouseState mouseState)
{

}



BulletSimulation::~BulletSimulation()
{
	TickEventManager::GetInstance().UnRegisterEvent(this);
	InputEventManager::GetInstance().UnRegisterEvent(this);
	m_BulletEntity.Destroy();
}

END_ENTERNITY


