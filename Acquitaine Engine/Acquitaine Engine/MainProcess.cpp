#include "MainProcess.h"
#include "GameProcess.h"
#include "SceneManager.h"

#pragma comment (lib,"Acquitaine Game Engine.lib")
#pragma comment(lib, "Acquitaine Game Client.lib")

constexpr int windowLength = 1280;
constexpr int windowHeight = 720;

constexpr int windowPositionX = 500;
constexpr int windowPositionY = 100;

HRESULT MainProcess::Initialize(HINSTANCE hInstance)
{
	// 디버깅, 테스트용 콘솔을 생성
 	AllocConsole();
	FILE* _tempFile;
	freopen_s(&_tempFile, "CONOUT$", "w", stdout);
	_deltatime = 0;
	_timer = new Timer();
	
	_gameprocess = new act::GameProcess();
	_gameprocess->Initialize();

	_gameClient = new SceneManager();
	_gameClient->Initialize();

	///
 	return S_OK;
}

void MainProcess::Loop()
{
	while (true)
	{
		if (PeekMessage(&_msg, NULL, 0, 0, PM_REMOVE))
		{
			if (_msg.message == WM_QUIT) break;
			DispatchMessage(&_msg);
		}
		else
		{
			// 델타 타임을 얻어오는 부분
			_timer->Update();
			_deltatime = _timer->GetDeltaTime();

			// 게임 엔진이 위치할 내용
			_gameprocess->RunningGameProcess(_deltatime);
		}
	}
}

void MainProcess::Finalize()
{
	_gameprocess->Finalize();
	delete _gameprocess;
	delete _gameClient;
}

LRESULT CALLBACK MainProcess::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE:
			break;
		case WM_RBUTTONDOWN:
			return 0;
		case WM_RBUTTONUP:
			return 0;
		case WM_MOUSEMOVE:
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			FreeConsole();
			return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
