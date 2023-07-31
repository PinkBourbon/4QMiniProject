module;
#include <vector>
#include <string>

export module aptoCore.rawData.RawMesh;

namespace aptoCore
{
	struct RawNode;
}

export namespace aptoCore
{
	struct RawMesh
	{
		RawMesh();

		std::wstring albedoMap;
		std::wstring normalMap;
		std::wstring roughnessMap;
		std::wstring metallicMap;
		std::wstring emissiveMap;
		std::wstring ambientOcclusionMap;

		std::vector<RawNode*> rootNodes;
		std::vector<RawNode*> rootBone;
		float minAnimFrame;
		float maxAnimFrame;
	};



}
