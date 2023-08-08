module;
#include <string>

export module aptoCore.rawData.RawMesh;

import aptoCore.rawData.RawMaterial;

export namespace aptoCore
{
	struct RawMesh
	{
		RawMesh() :
			minAnimFrame(0.0f), maxAnimFrame(0.0f)
		{}


		float minAnimFrame;
		float maxAnimFrame;
	};
}
