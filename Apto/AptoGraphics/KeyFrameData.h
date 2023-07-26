#pragma once

#include <vector>

import apto.math.Quaternion;
import apto.math.Vector3f;

namespace aptoCore
{
	struct KeyFrameData
	{
		KeyFrameData();

		apto::Vector3f GetPosition();
		apto::Quaternion GetQuaternion();

		std::vector<std::pair<float, apto::Vector3f>> pos;
		float MinPosAnimTime;
		float MaxPosAnimTime;
		float currPosAnimTime;

		unsigned int lastPosIndex;

		std::vector<std::pair<float, apto::Quaternion>> rot;
		float MinRotAnimTime;
		float MaxRotAnimTime;
		float currRotAnimTime;

		unsigned int lastRotIndex;
	};
}
