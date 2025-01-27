#pragma once
#include <iostream>
#include "raylib.h"
#include <vector>
#include <math.h>

#include "mathfunctions.hpp"
#include "lancy_arrays.hpp"
#include "lancy_meshes.hpp"



#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else
#define GLSL_VERSION 100
#endif



namespace Settings {
	constexpr int WindowWidth{ 1600 };
	constexpr int WindowHeight{ 900 };
	constexpr int RenderWidth{ 1600 };
	constexpr int RenderHeight{ 900 };
	constexpr float RenderRatio{ (float)WindowHeight / (float)RenderHeight };
}