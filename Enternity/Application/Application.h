#pragma once

struct GLFWwindow;
namespace Enternity
{
	struct ApplicationDescription
	{
		unsigned int Width;
		unsigned int Height;
		const char* Title;
	};

    class Application
    {
        public:
			Application(const ApplicationDescription& desc);

			bool Initialize();
			void Finalize();
			void Run();
		private:
			ApplicationDescription m_appDescription;
			GLFWwindow* m_context;
    };
}

