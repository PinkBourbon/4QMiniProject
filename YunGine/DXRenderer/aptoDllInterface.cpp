#include <windows.h>
#include "IDX11Render.h"
#include "Renderable.h"

IDX11Render* g_renderer;

bool aptoCore::Graphics::Initialize()
{
	g_renderer = CreateRenderer();

	//g_renderer->Initialize(GetModuleHandle(NULL));
	g_renderer->Initialize();

	return true;
}

void aptoCore::Graphics::Finalize()
{
	g_renderer->Finalize();
	DeleteRenderer(g_renderer);
}


void aptoCore::Graphics::Render(float deltaTime)
{
	g_renderer->Render();
}


bool aptoCore::Graphics::Resize(unsigned __int32 screenWidth, unsigned __int32 screenHeight)
{
	return false;
}


void aptoCore::Graphics::RegisterObject(Renderable& object)
{

}


void aptoCore::Graphics::DeregisterObject(Renderable& object)
{

}
