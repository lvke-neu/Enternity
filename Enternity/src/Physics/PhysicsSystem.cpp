#include "PhysicsSystem.h"

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
}

PhysicsSystem::~PhysicsSystem()
{
	SAFE_DELETE_SET_NULL(m_Broadphase);
	SAFE_DELETE_SET_NULL(m_CollisionConfiguration);
	SAFE_DELETE_SET_NULL(m_CollisionDispatcher);
	SAFE_DELETE_SET_NULL(m_Solver);
	SAFE_DELETE_SET_NULL(m_PhysicsWorld);
}

void PhysicsSystem::AddEntityToPhysicsWorld(Entity& entity, bool isPlane /* = false */)
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
		if (isPlane)
		{
			shape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
		}
		else
			shape = new btBoxShape(btVector3(0.5f * tc.m_Scale.x, 0.5f * tc.m_Scale.y, 0.5f * tc.m_Scale.z));
		
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
		m_PhysicsWorld->stepSimulation(deltaTime, maxSubSteps);
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

END_ENTERNITY