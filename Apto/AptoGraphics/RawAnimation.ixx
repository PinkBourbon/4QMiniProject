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

		std::vector<std::pair<float, Vector3f>> pos;		// 애니메이션 프레임별 포지션 데이터
		std::vector<std::pair<float, Quaternion>> rot;		// 애니메이션 프레임별 회전 데이터
	};
}
