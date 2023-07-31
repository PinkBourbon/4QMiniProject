#pragma once
import apto.math.Vector3f;
import apto.math.Quaternion;

namespace aptoCore
{
	struct KeyFrameData
	{
		// frame, pos
		std::vector<std::pair<float, apto::Vector3f>> pos;
		float currPosFrame;

		// frame, rot
		std::vector<std::pair<float, apto::Quaternion>> rot;
		float currRotFrame;
	};
}