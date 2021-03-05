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

#define BIT(x) (1 << x)
