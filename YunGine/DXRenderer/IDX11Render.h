#pragma once
//#include <string>
#include <windows.h>

struct Renderable;

#ifdef YUNGINEDLLEXPORT
#define YUNGINEDLL extern"C" __declspec(dllexport)
#else
#define YUNGINEDLL extern"C" __declspec(dllimport)
#endif

class IDX11Render abstract
{
public:
	IDX11Render() {}
	virtual ~IDX11Render() {};	// 인터페이스 소멸자는 virtual로

	virtual long Initialize() abstract;

	virtual void Update(float deltaTime) abstract;
	virtual void Render() abstract;
	virtual void BeginRender(float red, float green, float blue, float alpha) abstract;
	virtual void DrawObject() abstract;
	virtual void EndRender()  abstract;

	virtual void Finalize() abstract;
};

// dll외부에서 사용가능한 함수라고 알려주는 것
YUNGINEDLL IDX11Render* CreateRenderer();
YUNGINEDLL void DeleteRenderer(IDX11Render* renderer);

// 용훈이형의 인터페이스에 맞췄음


YUNGINEDLL bool Initialize();
YUNGINEDLL void Finalize();
YUNGINEDLL void Render(float deltaTime);
YUNGINEDLL bool Resize(unsigned __int32 screenWidth, unsigned __int32 screenHeight);
YUNGINEDLL void RegisterObject(Renderable& object);
YUNGINEDLL void DeregisterObject(Renderable& object);
