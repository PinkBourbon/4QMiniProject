#pragma once
#include <vector>
#include "Resource.h"
#include "IBuilder.h"


namespace aptoCore
{
	struct Node;

	struct Mesh
	{
		Mesh() :
			rootNodes(),
			minAnimFrame(0.0f),
			maxAnimFrame(0.0f),
			currAnimFrame(0.0f)
		{};
		void Release();

		std::vector<Node*> rootNodes;
		float minAnimFrame;
		float maxAnimFrame;
		float currAnimFrame;
	};

	template struct Resource<Mesh>;

	struct MeshBuilder : public IBuilder<Mesh>
	{
	public:
		MeshBuilder(const std::wstring filePath) : IBuilder<Mesh>(filePath) {};

		virtual void* build() const override;
	};
}
