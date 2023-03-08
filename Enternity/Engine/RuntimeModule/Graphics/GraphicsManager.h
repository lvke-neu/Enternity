#pragma once
#include "RuntimeModule/Interface/IRuntimeModule.h"

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
	private:
		GLFWwindow* m_context;
	};
}