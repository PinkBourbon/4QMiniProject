#pragma once
#include <d3d11.h>
#include <cstddef>

import apto.math.Vector2f;
import apto.math.Vector3f;
import apto.math.Vector4f;

namespace aptoCore
{
	struct Vertex
	{
		using type = struct
		{
			apto::Vector3f pos;
			apto::Vector3f tex;
			apto::Vector3f normal;
			apto::Vector3f tangent;
			apto::Vector4f color;
			UINT boneIndices[4];
			float boneWeights[4];
		};

		static constexpr unsigned int numElements = 13;
		static constexpr D3D11_INPUT_ELEMENT_DESC layout[numElements] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(type, pos), D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(type, tex), D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(type, normal), D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(type, tangent), D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(type, color), D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"BLENDINDICES", 0, DXGI_FORMAT_R32_UINT , 0, offsetof(type, boneIndices[0]), D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"BLENDINDICES", 1, DXGI_FORMAT_R32_UINT , 0, offsetof(type, boneIndices[1]), D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{"BLENDINDICES", 2, DXGI_FORMAT_R32_UINT , 0, offsetof(type, boneIndices[2]), D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{"BLENDINDICES", 3, DXGI_FORMAT_R32_UINT , 0, offsetof(type, boneIndices[3]), D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{"BLENDWEIGHT", 0, DXGI_FORMAT_R32_FLOAT, 0, offsetof(type, boneWeights[0]), D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{"BLENDWEIGHT", 1, DXGI_FORMAT_R32_FLOAT, 0, offsetof(type, boneWeights[1]), D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{"BLENDWEIGHT", 2, DXGI_FORMAT_R32_FLOAT, 0, offsetof(type, boneWeights[2]), D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{"BLENDWEIGHT", 3, DXGI_FORMAT_R32_FLOAT, 0, offsetof(type, boneWeights[3]), D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
	};
}
