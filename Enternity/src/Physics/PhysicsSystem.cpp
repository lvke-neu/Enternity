#include "PhysicsSystem.h"
#include "Renderer/RenderSystem.h"
#include "Scene/SceneManager.h"

BEGIN_ENTERNITY

PhysicsSystem::PhysicsSystem()
{
	//create world
	btVector3 worldAabbMin(-10000, -10000, -10000);
	btVector3 worldAabbMax(10000, 10000, 10000);
	int maxProxies = 1024;
	btAxisSweep3* broadphase = new btAxisSweep3(worldAabbMin, worldAabbMax, maxProxies);
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
	m_PhysicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	m_PhysicsWorld->setGravity(btVector3(0.0f, -9.8f, 0.0f));

	//create collider shape 
	m_BoxColliderShape = Entity(SceneManager::GetInstance().GetRegistry(), "Box Collider Shape");
	m_BoxColliderShape.AddComponent<TransformComponent>();
	auto& matc = m_BoxColliderShape.AddComponent<MaterialComponent>();
	auto& meshc = m_BoxColliderShape.AddComponent<MeshComponent>();
	matc.m_BaseColor = glm::vec4(0, 1, 0, 1);
	matc.m_bUseColor = true;
	matc.m_ShaderFilePath = "assets/shaders/TestECS.glsl";
	meshc.m_MeshFilePath = "assets/models/cube.mesh";
	matc.Load();
	meshc.Load();
}

PhysicsSystem::~PhysicsSystem()
{
	SAFE_DELETE_SET_NULL(m_Broadphase);
	SAFE_DELETE_SET_NULL(m_CollisionConfiguration);
	SAFE_DELETE_SET_NULL(m_CollisionDispatcher);
	SAFE_DELETE_SET_NULL(m_Solver);
	SAFE_DELETE_SET_NULL(m_PhysicsWorld);

	//destroy collider shape
	m_BoxColliderShape.Destroy();
}

void PhysicsSystem::AddEntityToPhysicsWorld(Entity& entity)
{
	if (entity.HasComponent<RigidBodyComponent>()
		&& entity.HasComponent<TransformComponent>())
	{
		auto& rbc = entity.GetComponent<RigidBodyComponent>();
		auto& tc = entity.GetComponent<TransformComponent>();

		//create rigidbody and add it to world
		auto quant = glm::qua<float>(tc.m_Rotation);
		auto trans = tc.m_Translation;
		btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(quant.x, quant.y, quant.z, quant.w), btVector3(trans.x, trans.y, trans.z)));
		btCollisionShape* shape{ nullptr };

		switch (rbc.m_ColliderShape)
		{
		case RigidBodyComponent::ColliderShape::Box:
			shape = new btBoxShape(btVector3(tc.m_Scale.x, tc.m_Scale.y, tc.m_Scale.z));
			break;
		case RigidBodyComponent::ColliderShape::Sphere:
			shape = new btSphereShape(1);
			break;
		}
		
		btVector3 inertia;
		shape->calculateLocalInertia(rbc.m_Mass, inertia);
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(rbc.m_Mass, ballMotionState, shape, inertia);
		btRigidBody* rigidBody = new btRigidBody(groundRigidBodyCI);

		
		rigidBody->setFriction(rbc.m_Friction);
		rigidBody->setRestitution(rbc.m_Restitution);
		rbc.m_RigidBody = rigidBody;
		m_PhysicsWorld->addRigidBody(rigidBody);
	}
}

void PhysicsSystem::RemoveEntityFromPhysicsWorld(Entity& entity)
{
	if (entity.HasComponent<RigidBodyComponent>())
	{
		auto& rbc = entity.GetComponent<RigidBodyComponent>();
		btRigidBody* body = (btRigidBody*)rbc.m_RigidBody;

		btCollisionShape* shape{ nullptr };
		btDefaultMotionState* ballMotionState{ nullptr };
		if (body)
		{
			shape = body->getCollisionShape();
			ballMotionState = dynamic_cast<btDefaultMotionState*>(body->getMotionState());
		}

		m_PhysicsWorld->removeRigidBody((btRigidBody*)body);
		body->setCollisionShape(nullptr);
		body->setMotionState(nullptr);
		rbc.m_RigidBody = nullptr;

		SAFE_DELETE_SET_NULL(shape);
		SAFE_DELETE_SET_NULL(ballMotionState);
		SAFE_DELETE_SET_NULL(body);
	}	
}

void PhysicsSystem::StepSimulation(float deltaTime, int maxSubSteps /* = 10 */)
{
	if (m_PhysicsWorld)
		m_PhysicsWorld->stepSimulation(deltaTime, 10);
}

void PhysicsSystem::UpdateEntityState(Entity& entity)
{
	if (entity.HasComponent<RigidBodyComponent>()
		&& entity.HasComponent<TransformComponent>())
	{
		auto& rbc = entity.GetComponent<RigidBodyComponent>();
		auto& tc = entity.GetComponent<TransformComponent>();

		btRigidBody* body = (btRigidBody*)rbc.m_RigidBody;
		if (body)
		{
			auto trans = body->getWorldTransform().getOrigin();
			tc.m_Translation.x = trans.x();
			tc.m_Translation.y = trans.y();
			tc.m_Translation.z = trans.z();
			auto rotation = body->getWorldTransform().getRotation();
			rotation.getEulerZYX(tc.m_Rotation.z, tc.m_Rotation.y, tc.m_Rotation.x);
		}
	}
}

void PhysicsSystem::ShowBoxColliderShape(const glm::vec3& pos, const glm::vec3& offset)
{
	auto& transc = m_BoxColliderShape.GetComponent<TransformComponent>();
	transc.m_Translation = pos;
	transc.m_Scale.x = offset.x;
	transc.m_Scale.y = offset.y;
	transc.m_Scale.z = offset.z;

	RenderSystem::GetInstance().DrawColliderShape(SceneManager::GetInstance().GetCurrentCameraEntity(), m_BoxColliderShape);

}


END_ENTERNITY

