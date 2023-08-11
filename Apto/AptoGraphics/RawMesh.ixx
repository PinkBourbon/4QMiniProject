module;
#include <string>
#include <vector>
#include "Vertex.h"

export module aptoCore.rawData.RawMesh;

import aptoCore.rawData.RawMaterial;
import aptoCore.rawData.RawSkin;

export namespace aptoCore
{
	struct RawMesh
	{
		RawMesh() :
			minAnimFrame(0.0f), maxAnimFrame(0.0f)
		{}

		float minAnimFrame;
		float maxAnimFrame;

		std::vector<Vertex::type> vertices;
		std::vector<int> indices;
		RawSkin skin;

		RawMaterial* material;
	};
}
