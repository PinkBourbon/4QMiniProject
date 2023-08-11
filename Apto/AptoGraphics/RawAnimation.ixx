module;
#include <vector>
export module aptoCore.rawData.RawAnimation;

import apto.math.Vector3f;
import apto.math.Quaternion;

export namespace aptoCore
{
	struct RawAnimation
	{
		using Vector3f = apto::Vector3f;
		using Quaternion = apto::Quaternion;

		std::vector<std::pair<float, Vector3f>> pos;
		std::vector<std::pair<float, Quaternion>> rot;
	};
}
