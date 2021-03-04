#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>
namespace TinyEngine
{
	class TINY_API Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }


	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define TI_CORE_TRACE(...)	::TinyEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TI_CORE_INFO(...)	::TinyEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TI_CORE_WARN(...)	::TinyEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TI_CORE_ERROR(...)	::TinyEngine::Log::GetCoreLogger()->error(__VA_ARGS__)

//Client log macros
#define TI_TRACE(...)	::TinyEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TI_INFO(...)	::TinyEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define TI_WARN(...)	::TinyEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TI_ERROR(...)	::TinyEngine::Log::GetClientLogger()->error(__VA_ARGS__)