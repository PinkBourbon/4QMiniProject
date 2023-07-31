#include <windows.h>
#include "IDX11Render.h"
#include "Renderable.h"

IDX11Render* g_renderer;

bool Initialize()
{
	g_renderer = CreateRenderer();

	g_renderer->Initialize(GetModuleHandle(NULL));

	return true;
}


void Finalize()
{
	g_renderer->Finalize();
	DeleteRenderer(g_renderer);
}


void Render(float deltaTime)
{
	g_renderer->Render();
}


bool Resize(unsigned __int32 screenWidth, unsigned __int32 screenHeight)
{
	return false;
}


void RegisterObject(Renderable& object)
{

}


void DeregisterObject(Renderable& object)
{

}
