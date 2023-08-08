module;
#include <string>
#include <vector>
export module aptoCore.rawData.RawNode;

import aptoCore.rawData.RawMesh;

export namespace aptoCore
{
	struct RawNode
	{
		std::wstring name;

		std::vector<RawNode*> children;
		
		RawMesh* mesh;
	};
}
