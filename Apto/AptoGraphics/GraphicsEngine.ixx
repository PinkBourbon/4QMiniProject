module;
#include <windows.h>
export module aptoCore.Graphics;

export import aptoCore.Renderable;

export namespace aptoCore::Graphics
{
	__declspec(dllexport) bool Initialize();

	__declspec(dllexport) void Finalize();

	__declspec(dllexport) void Render(float deltaTime);

	__declspec(dllexport) bool Resize(unsigned __int32 screenWidth, unsigned __int32 screenHeight);

	__declspec(dllexport) void RegisterObject(Renderable& object);

	__declspec(dllexport) void DeregisterObject(Renderable& object);

	__declspec(dllexport) bool isRunEngine();
}


//module : private;

namespace aptoCore::Graphics
{
	HWND InitializeWindow(int windowWidth, int windowHeight);

	bool InitDisplayInfo();

	bool InitGPUInfo();

	bool OnResize();
}