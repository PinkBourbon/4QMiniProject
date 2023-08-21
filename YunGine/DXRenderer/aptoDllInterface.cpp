#include "IDX11Render.h"
#include "Renderable.h"

IDX11Render* g_renderer;

bool Initialize()
{
	g_renderer = CreateRenderer();

	g_renderer->Initialize();

	return true;
}

void Finalize()
{
	g_renderer->Finalize();
	DeleteRenderer(g_renderer);
}


void Render(float deltaTime)
{
	g_renderer->Update(deltaTime);
	g_renderer->Render();
}


bool Resize(unsigned __int32 screenWidth, unsigned __int32 screenHeight)
{
	return false;
}


YUNGINEDLL void RegisterObject(aptoCore::Renderable& object)
{
	g_renderer->RegisterObject(object);
}


YUNGINEDLL void DeregisterObject(aptoCore::Renderable& object)
{
	g_renderer->DeregisterObject(object);
}
