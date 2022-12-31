/***************************************************************************************
Author: lvke
Date:2022/12/31 10:04
Description:
Log
****************************************************************************************/
#pragma once
#include <spdlog/spdlog.h>
#include "Macro/Macro.h"

BEGIN_ENTERNITY

class Log
{
	SINGLETON(Log);
public:
	enum LogLevel
	{
		debug,
		info,
		warn,
		error,
		fatal
	};
private:
	Log();
	~Log();
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete;

public:
	template<typename... TARGS>
	void log(LogLevel level, TARGS&&... args)
	{
		switch (level)
		{
		case LogLevel::debug:
			m_logger->debug(std::forward<TARGS>(args)...);
			break;
		case LogLevel::info:
			m_logger->info(std::forward<TARGS>(args)...);
			break;
		case LogLevel::warn:
			m_logger->warn(std::forward<TARGS>(args)...);
			break;
		case LogLevel::error:
			m_logger->error(std::forward<TARGS>(args)...);
			break;
		case LogLevel::fatal:
			m_logger->critical(std::forward<TARGS>(args)...);
			fatalCallback(std::forward<TARGS>(args)...);
			break;
		default:
			break;
		}
	}
	template<typename... TARGS>
	void fatalCallback(TARGS&&... args)
	{
		const std::string format_str = fmt::format(std::forward<TARGS>(args)...);
		throw std::runtime_error(format_str);
	}

private:
	std::shared_ptr<spdlog::logger> m_logger;
};

#define LOG_HELPER(LOG_LEVEL, ...) \
		Enternity::Log::GetInstance().log(LOG_LEVEL, "[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__);

#define LOG_DEBUG(...) LOG_HELPER(Enternity::Log::LogLevel::debug, __VA_ARGS__);

#define LOG_INFO(...) LOG_HELPER(Enternity::Log::LogLevel::info, __VA_ARGS__);

#define LOG_WARN(...) LOG_HELPER(Enternity::Log::LogLevel::warn, __VA_ARGS__);

#define LOG_ERROR(...) LOG_HELPER(Enternity::Log::LogLevel::error, __VA_ARGS__);

#define LOG_FATAL(...) LOG_HELPER(Enternity::Log::LogLevel::fatal, __VA_ARGS__);


END_ENTERNITY

