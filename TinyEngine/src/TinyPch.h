#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <sstream>
#include <fstream>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Tiny/Core/Log.h"
#include "Tiny/Debug/Instrumentor.h"

#ifdef TI_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
