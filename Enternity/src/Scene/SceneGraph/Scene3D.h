#pragma once
#include "Engine/Scene.h"

namespace Enternity 
{
	class Scene3D : public Scene
	{
	public:
		Scene3D();
		~Scene3D();
	private:
		void initCamera();
		void initBaseScene();
		void initObjcet();
	};
}