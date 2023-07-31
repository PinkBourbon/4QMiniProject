#pragma once
//#include <string>

struct Renderable;

class IDX11Render abstract
{
public:
	IDX11Render() {}
	virtual ~IDX11Render() {};	// 인터페이스 소멸자는 virtual로

	virtual long Initialize(void* hwnd) abstract;

	virtual void Update(float deltaTime) abstract;
	virtual void Render() abstract;
	virtual void BeginRender(float red, float green, float blue, float alpha) abstract;
	virtual void DrawObject() abstract;
	virtual void EndRender()  abstract;

	virtual void Finalize() abstract;
};

// dll외부에서 사용가능한 함수라고 알려주는 것
extern "C" __declspec(dllexport) IDX11Render * CreateRenderer();
extern "C" __declspec(dllexport) void DeleteRenderer(IDX11Render * renderer);

// 용훈이형의 인터페이스에 맞췄음
extern "C" __declspec(dllexport) bool Initialize();
extern "C" __declspec(dllexport) void Finalize();
extern "C" __declspec(dllexport) void Render(float deltaTime);
extern "C" __declspec(dllexport) bool Resize(unsigned __int32 screenWidth, unsigned __int32 screenHeight);
extern "C" __declspec(dllexport) void RegisterObject(Renderable & object);
extern "C" __declspec(dllexport) void DeregisterObject(Renderable & object);

