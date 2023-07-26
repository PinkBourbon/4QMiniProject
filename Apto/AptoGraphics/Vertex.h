#pragma once
#include <d3d11.h>
#include <cstddef>

import apto.math.Vector2f;
import apto.math.Vector3f;
import apto.math.Vector4f;

namespace aptoCore
{
	struct Vertrex
	{
		using type = struct
		{
			apto::Vector3f Pos;
			apto::Vector3f UV;
			apto::Vector3f Normal;
			apto::Vector3f Tangent;
			apto::Vector4f Color;
		};

		static constexpr unsigned int numElements = 5;
		static constexpr D3D11_INPUT_ELEMENT_DESC layout[numElements] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(type, Pos), D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(type, UV), D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(type, Normal), D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(type, Tangent), D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(type, Color), D3D11_INPUT_PER_VERTEX_DATA, 0}
		};
	};
}