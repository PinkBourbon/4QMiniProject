module;
#include <string>
#include <vector>
#include <memory>
export module aptoCore.rawData.RawNode;

import aptoCore.rawData.RawMesh;
import aptoCore.rawData.RawAnimation;

export namespace aptoCore
{
	struct RawNode
	{
		RawNode(const std::wstring& name) : name(name), mesh(nullptr), animation(nullptr) {}
		~RawNode()
		{
			for (auto& child : children)
			{
				delete child;
			}
		}

		std::wstring name;

		std::vector<RawNode*> children;

		std::unique_ptr<RawMesh> mesh;
		std::unique_ptr<RawAnimation> animation;
	};
}
