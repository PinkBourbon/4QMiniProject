module;
#include <string>
#include <vector>
#include <memory>
#include "Vertex.h"
export module aptoCore.rawData.RawMesh;

import aptoCore.rawData.RawMaterial;
import aptoCore.rawData.RawSkin;

export namespace aptoCore
{
	struct RawMesh
	{
		RawMesh() :
			vertices(), indices(),
			skin(), material()
		{}

		std::vector<Vertex::type> vertices;
		std::vector<int> indices;
		RawSkin skin;

		RawMaterial material;
	};
}
