/***************************************************************************************
Author: lvke
Date:2023/1/14 23:52
Description:
Scene Serializer
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"
#include "SceneManager.h"
#include <yaml-cpp/yaml.h>

BEGIN_ENTERNITY

class SceneSerializer
{
public:
	static void Serialize(const std::string& filePath);
private:
	static void SerializeEntity(YAML::Emitter& out, Entity entity);
};

END_ENTERNITY