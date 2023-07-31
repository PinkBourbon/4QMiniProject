#pragma once
import apto.Transform;

#include <string>
#include <vector>
#include "KeyFrameData.h"

struct ID3D11Buffer;

namespace aptoCore
{
	struct Node
	{
		std::string name;
		const apto::Transform initTransform;
		const apto::Matrix4f initNodeToWorldTransform;

		apto::Transform tr;
		Node* parent;
		std::vector<Node*> children;

		ID3D11Buffer* vertexBuffer;
		size_t singleVertexSize;
		ID3D11Buffer* indexBuffer;
		size_t indexCount;

		KeyFrameData keyFrameData;

		bool isBone;
		unsigned int boneIndex;

		int topology;
	};
}

