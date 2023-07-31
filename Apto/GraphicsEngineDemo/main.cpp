#include <iostream>
#include "Vertex.h"

import apto.math;
import apto.util.Time;
import apto.Graphics.Camera;
import aptoCore.Graphics;

bool isResize = false;

int main()
{
	/*constexpr apto::Vector4f v1(1.0f, 2.0f, 3.0f, 4.0f);

	std::cout << v1.x << std::endl;

	apto::Camera camera;
	camera.SetPosition(0.f, 0.f, -10.f);
	camera.SetRotation(0.f, 0.f, 0.f);
	camera.SetPropeties(1920.f, 1080.f, 60.f, 0.1f, 10000.f);
	camera.SetPerspective();

	apto::Matrix4f mat = camera.GetProjectionMatrix4f();

	camera.AddPosition(1.0f, 2.0f, 3.0f);
	camera.AddRotationAxis(apto::Vector3f(1.0f, 0.0f, 0.0f), 0.1f);

	apto::Matrix4f mat2 = camera.GetViewMatrix4f();*/

	aptoCore::Graphics::Initialize();

	if (!isResize)
	{
		aptoCore::Graphics::Resize(1920, 1080);
		isResize = !isResize;
	}

	while (aptoCore::Graphics::isRunEngine())
	{
		aptoCore::Graphics::Render(1.0f);
	}

	aptoCore::Graphics::Finalize();

	return 0;
}