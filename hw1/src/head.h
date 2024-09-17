#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

#include <math.h>
#include <limits>
#include <string>

namespace mms
{
	const std::string assets_path = "assets/hw1/";
	const std::string shaders_path = "shaders/hw1/";

	constexpr float EPSILON = 0.001f;
	constexpr float Pi = 3.1415926f;
	
	inline bool NearZero(float val, float epsilon = 0.001f)
	{
		return (fabs(val) <= epsilon);
	}


	constexpr glm::vec3 AxisY = glm::vec3(0.f, 1.f, 0.f);
	constexpr glm::vec3 AxisX = glm::vec3(1.f, 0.f, 0.f);
}