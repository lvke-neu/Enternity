#pragma once

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <memory>
#pragma warning(pop)

namespace Enternity {

	class Log
	{
	public:
		static void Init();
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;

	};

}

#define LOG_TRACE(...)    ::Enternity::Log::GetCoreLogger()->trace("[" + std::string(__FUNCTION__) + "]:" +  __VA_ARGS__)
#define LOG_INFO(...)     ::Enternity::Log::GetCoreLogger()->info("[" + std::string(__FUNCTION__) + "]:" + __VA_ARGS__)
#define LOG_WARN(...)     ::Enternity::Log::GetCoreLogger()->warn("[" + std::string(__FUNCTION__) + "]:" + __VA_ARGS__)
#define LOG_ERROR(...)    ::Enternity::Log::GetCoreLogger()->error("[" + std::string(__FUNCTION__) + "]:" + __VA_ARGS__)
#define LOG_CRITICAL(...) ::Enternity::Log::GetCoreLogger()->critical("[" + std::string(__FUNCTION__) + "]:" + __VA_ARGS__)

