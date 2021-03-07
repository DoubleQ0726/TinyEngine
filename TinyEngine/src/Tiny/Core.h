#pragma once

#ifdef TI_PLATFORM_WINDOWS
	#ifdef TI_BUILD_DLL
		#define TINY_API __declspec(dllexport)
	#else
		#define TINY_API __declspec(dllimport) 
	#endif // TI_BUILD_DLL
#else
	#error Tiny only support Windows!
#endif // TI_PLATFORM_WINDOWS

#ifdef TI_ENABLE_ASSERTS
	#define TI_ASSERT(x, ...) { if (!(x)) { TI_ERROR("Assertion Failed: {0}", __VA__ARGS__); __debugbreak(); } }
	#define TI__CORE_ASSERT(x, ...) { if (!(x)) { TI_CORE_ERROR("Assertion Failed: {0}", __VA__ARGS__); __debugbreak(); } }

#else
	#define TI_ASSERT(x, ...)
	#define TI_CORE_ASSERT(x, ...) 
#endif // TI_ENABLE_ASSERT


#define BIT(x) (1 << x)

#define TI_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
