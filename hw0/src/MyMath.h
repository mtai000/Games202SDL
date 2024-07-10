#pragma once
#include <math.h>
#include <limits>
#include <glm/glm.hpp>

namespace MyMath
{
	constexpr float EPSILON = 0.001f;
	constexpr float Pi = 3.1415926f;

	inline bool NearZero(float val, float epsilon = 0.001f)
	{
		return (fabs(val) <= epsilon);
	}


	constexpr glm::vec3 AxisY = glm::vec3(0.f, 1.f, 0.f);
}