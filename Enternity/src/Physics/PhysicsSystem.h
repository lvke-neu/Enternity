/***************************************************************************************
Author: lvke
Date:2023/1/21 17:50
Description:
Physics System (3D)
****************************************************************************************/

#pragma once

#include "Macro/Macro.h"
#include "Scene/ECS/Entity/Entity.h"
#include "Scene/ECS/Component/Component.h"
#include <btBulletDynamicsCommon.h>

BEGIN_ENTERNITY

class PhysicsSystem
{
	SINGLETON(PhysicsSystem);
private:
	PhysicsSystem();
	~PhysicsSystem();
	PhysicsSystem(const PhysicsSystem&) = default;
	PhysicsSystem& operator=(const PhysicsSystem&) = default;
public:
	void AddEntityToPhysicsWorld(Entity& entity, bool isPlane = false);
	void RemoveEntityFromPhysicsWorld(Entity& entity);
	void StepSimulation(float deltaTime, int maxSubSteps = 10);
	void UpdateEntityState(Entity& entity);
private:
	btAxisSweep3* m_Broadphase{ nullptr };
	btDefaultCollisionConfiguration* m_CollisionConfiguration{ nullptr };
	btCollisionDispatcher* m_CollisionDispatcher{ nullptr };
	btSequentialImpulseConstraintSolver* m_Solver{ nullptr };
	btDiscreteDynamicsWorld* m_PhysicsWorld{ nullptr };
};

END_ENTERNITY