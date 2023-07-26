module;
#include <cmath>

module apto.math.Common;

// import <cmath>;

namespace apto
{
	float DegToRad(float degree)
	{
		return std::fmod(degree, 360.0f) * PI<float> / 180.f;
	}

	float RadToDeg(float radian)
	{
		return std::fmod(radian, 2.f * PI<float>) * 180.f / PI<float>;
	}
}