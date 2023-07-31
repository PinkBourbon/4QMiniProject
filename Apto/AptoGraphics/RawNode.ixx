module;
#include <vector>
#include <string>
export module aptoCore.rawData.RawNode;

import apto.Transform;
import apto.math.Matrix4f;
import aptoCore.rawData.RawKeyFrameData;

export namespace aptoCore
{
	struct RawNode
	{
		std::string name;
		apto::Transform transform;
		apto::Matrix4f worldMatrix;

		RawNode* parent;
		std::vector<RawNode*> children;

		bool isSkinnedNode;

		// 내가 bone이 아니라면 인덱스 값은 -1
		// bone이라면 0 이상
		int boneIndex;

		// 노드별 애니메이션을 위한 데이터.
		RawKeyFrameData keyFrameData;
	};
}