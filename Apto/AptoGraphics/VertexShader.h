#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Resource.h"
#include "IBuilder.h"
#include "AptoMacro.h"

namespace aptoCore
{
	struct VertexShader
	{
		void Release();
	};

	void VertexShader::Release()
	{

	}

	template struct Resource<VertexShader>;

	struct VertexShaderBuilder : public IBuilder<VertexShader>
	{
	public:
		VertexShaderBuilder(const std::wstring filePath) : IBuilder<VertexShader>(filePath) {};

		virtual void* Build() override;
	};

	void* VertexShaderBuilder::Build()
	{
		UINT flags1 = 0;
#if defined(_DEBUG) || defined(_DEBUG)
		flags1 |= D3DCOMPILE_DEBUG;
#endif

		ID3D10Blob* vertexShaderBlob = nullptr;
		HRESULT hresult = D3DCompileFromFile(key.c_str(), nullptr, nullptr, "main", "vs_5_0", flags1, 0, &vertexShaderBlob, nullptr);

		if (hresult != S_OK)
		{
			APTO_ASSERT(false, "vertex shader complie fail");
			return nullptr;
		}

		ID3D11VertexShader* vertexShader = nullptr;
		hresult = g
	}

}
