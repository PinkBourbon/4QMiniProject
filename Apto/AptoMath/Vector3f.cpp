module;

#include "AptoMacro.h"

module apto.math.Vector3f;

apto::Vector3f apto::Vector3f::Lerp(const apto::Vector3f& v0, const apto::Vector3f& v1, float t) noexcept
{
	APTO_ASSERT(t >= 0.0f && t <= 1.0f, "");
	return v0 + (v1 - v0) * t;
};
