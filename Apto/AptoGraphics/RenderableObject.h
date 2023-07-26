#pragma once
#include "Resource.h"

namespace apto
{
	struct Renderable;
	class Transform;
}

namespace aptoCore
{
	struct Mesh;
	struct VertexShader;
	struct PixelShader;

	class RenderableObject
	{
	public:
		//RenderableObject(apto::Renderable& renderable);

		void Render();
	private:
		apto::Transform* _transform;
		//Resource<Mesh> _mesh;
		//Resource<VertexShader> _vertexShader;
		//Resource<PixelShader> _pixelShader;
	};
}



