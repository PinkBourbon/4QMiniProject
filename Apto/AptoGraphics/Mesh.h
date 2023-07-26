#pragma once
#include <vector>
#include "Resource.h"
#include "IBuilder.h"

namespace aptoCore
{
	struct Node;

	struct Mesh
	{
		std::vector<Node*> rootNodes;
		void Release();
	};

	template struct Resource<Mesh>;

	struct MeshBuilder : public IBuilder<Mesh>
	{
	public:
		MeshBuilder(const std::string filePath) : IBuilder<Mesh>(filePath) {};

		virtual void* build() const override;
	};
}
