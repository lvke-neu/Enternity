#pragma once

namespace Enternity
{
	class IScene
	{
	public:
		virtual void Initialize() = 0;
		virtual void Finalize() = 0;
		virtual void Tick(float deltaTime) = 0;
		virtual void OnResize(int width, int height) {};
		virtual void RecompileShader() = 0;
		virtual void RenderGUI() {};
	protected:
		bool m_bIsInit = false;
	};
}