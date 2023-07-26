module;
#include <vector>
#include <string>

export module aptoCore.rawData.RawMesh;

namespace aptoCore
{
	struct RawDataNode;
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

		std::vector<RawDataNode*> rootNodes;
		std::vector<RawDataNode*> rootBone;
		float minAnimFrame;
		float maxAnimFrame;
	};



}
