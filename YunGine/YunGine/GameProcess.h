#pragma once
#include <windows.h>
#include <memory>
#include "..\\DXRenderer\\IDX11Render.h"	// dll에 있는 헤더 쓰겠다
#include "GameTimer.h"

#ifdef _DEBUG
#define RENDER_PATH L"..\\x64\\debug\\DXRenderer.dll"
#pragma comment(lib, "..\\x64\\debug\\DXRenderer.lib")		// 이 lib를 쓰겠다
#else					
#define RENDER_PATH L"..\\x64\\release\\DXRenderer.dl"
#pragma comment(lib, "..\\x64\\release\\DXRenderer.lib")		// 이 lib를 쓰겠다
#endif // _DEBUG

/// <summary>
/// 수업시간에 만든 게임 엔진의 최외곽 부분
/// 
/// 길잃은 어린양을 구원해주세요
/// 
/// 23.06.16 -Dispact-
/// </summary>

import aptoCore.Renderable;
import apto.Transform;

class MyCube
{
public:
	MyCube()
	{
		renderable.MeshFilePath = "Cube";
		renderable.objectTransform = &transform;
	}
public:

	aptoCore::Renderable renderable;
	apto::Transform transform;
};

class Test
{
public:
	Test()
	{
		renderable.MeshFilePath = "..\\Resource\\SpaceShip.fbx";
		renderable.objectTransform = &transform;
	}

	aptoCore::Renderable renderable;
	apto::Transform transform;
};


class GameProcess
{
public:
	GameProcess() = default;
	~GameProcess();

private:
	// 공통적인 설정

	// 화면의 크기
	const int _screenWidth = 1920;
	const int _screenHeight = 1080;

	// 윈도 관련
	HWND _hWnd;
	MSG _msg;
	
	// 그래픽스 엔진
	HMODULE _hModule;
	HINSTANCE _hInstance;
	
	// 게임 타이머
	GameTimer* _timer;

public:
	// 게임용 윈도 프레임웍을 초기화한다.
	HRESULT MyInitialize(HINSTANCE hInstance);

	// 메인 게임 루프. 실제 게임이 진행되는 반복구문
	void Loop();

	void Update();
	void Render();
	
	HRESULT CreateGraphicEngine();
	HRESULT DeleteGraphicEngine();

	// 게임을 정리한다.
	void Finalize();

	// 메시지 핸들러 (윈도 콜백)
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	MyCube testCube;
	MyCube testCube1;
	MyCube testCube2;
	MyCube testCube3;
	MyCube testCube4;

	Test myTest;
};

