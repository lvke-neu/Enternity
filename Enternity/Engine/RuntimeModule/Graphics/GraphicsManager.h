#pragma once
#include "RuntimeModule/Interface/IRuntimeModule.h"
#include "Core/Math/Vector.h"

struct GLFWwindow;
namespace Enternity
{
	class GraphicsManager : public IRuntimeModule
	{
	public:
		virtual ~GraphicsManager() = default;

		virtual bool Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;

		bool IsQuit() const;
		void setClearColor(const Vector3f& color);
	private:
		GLFWwindow* m_context;
		Vector3f m_color{0.5f, 0.6f, 0.7f };
	};
}