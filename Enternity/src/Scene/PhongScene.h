#pragma once
#include "Interface/SceneInterface.h"
#include <vector>

namespace Enternity
{


	class Camera3D;
	class CameraController;
	class Light;
	class CubeObject;
	class PhongScene : public IScene
	{
		friend class GUIRender;
	public:
		virtual void Initialize() override;
		virtual void Finalize() override;
		virtual void Tick(float deltaTime) override;
		virtual void RecompileShader() override;
		virtual void RenderGUI() override;
		virtual void OnResize(int width, int height) override;
	private:
		Camera3D* m_pCamera3D;
		CameraController* m_pCameraController;
		Light* m_pLight;
		std::vector<CubeObject*> m_pCubeObjects;
	};
}