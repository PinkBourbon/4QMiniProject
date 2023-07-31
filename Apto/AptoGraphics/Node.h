#pragma once

#include <string>
#include <vector>
#include <memory>
#include <wrl/client.h>
#include "KeyFrameData.h"

import apto.Transform;


struct ID3D11Buffer;

namespace aptoCore
{
	struct Node
	{
		template<typename T>
		using comptr = Microsoft::WRL::ComPtr<T>;

		std::string name;
		const apto::Transform initTransform;
		const apto::Matrix4f initNodeToWorldTransform;

		apto::Transform tr;
		Node* parent;
		std::vector< std::unique_ptr<Node> > children;

		comptr<ID3D11Buffer> vertexBuffer;
		size_t singleVertexSize;
		comptr<ID3D11Buffer> indexBuffer;
		size_t indexCount;

		KeyFrameData keyFrameData;

		bool isBone;
		unsigned int boneIndex;

		int topology;
	};
}

