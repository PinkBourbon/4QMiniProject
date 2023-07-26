#pragma once
#include <d3d11.h>
#include "Resource.h"
#include "IBuilder.h"

namespace aptoCore
{
	struct VertexShader
	{
		void Release();
	};

	template struct Resource<VertexShader>;

	struct VertexShaderBuilder : public IBuilder<VertexShader>
	{
	public:
		VertexShaderBuilder(const std::string filePath) : IBuilder<VertexShader>(filePath) {};

		virtual void* Build() override;
	};
}
