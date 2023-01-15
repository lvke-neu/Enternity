/***************************************************************************************
Author: lvke
Date:2023/1/14 23:52
Description:
Scene Serializer
****************************************************************************************/
#pragma once

#include <yaml-cpp/yaml.h>
#include "Macro/Macro.h"
#include "ECS/Entity/Entity.h"

BEGIN_ENTERNITY

class SceneSerializer
{
public:
	static void Serialize(const std::string& filePath);
	static bool Deserialize(const std::string& filePath);
private:
	static void SerializeEntity(YAML::Emitter& out, Entity entity);
};

END_ENTERNITY