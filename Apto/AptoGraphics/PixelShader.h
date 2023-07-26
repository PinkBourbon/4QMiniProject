#pragma once
#include <d3d11.h>
#include "Resource.h"
#include "IBuilder.h"

namespace aptoCore
{
	struct PixelShader
	{
		ID3D11PixelShader* shader;
		void Release();
	};

	template struct Resource<PixelShader>;

	struct PixelShaderBuilder : public IBuilder<PixelShader>
	{
	public:
		PixelShaderBuilder(const std::string filePath) : IBuilder<PixelShader>(filePath) {};

		virtual void* Build() override;
	};
}

