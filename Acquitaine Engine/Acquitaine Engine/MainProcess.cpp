#include "MainProcess.h"
#include "GameProcess.h"

#pragma comment (lib,"Acquitaine Game Engine.lib")

constexpr int windowLength = 1280;
constexpr int windowHeight = 720;

constexpr int windowPositionX = 500;
constexpr int windowPositionY = 100;

HRESULT MainProcess::Initialize(HINSTANCE hInstance)
{
	/// Win32 관련
	// 윈도 클래스
	LPCWSTR szAppName = L"Acquitain Project";
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = this->WindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	// 윈도 클래스 등록
	RegisterClass(&wndclass);

	// 윈도 생성
	_hWnd = CreateWindow(
		szAppName,
		szAppName,
		WS_OVERLAPPEDWINDOW,
		windowPositionX, windowPositionY, windowLength, windowHeight,
		NULL, NULL, hInstance, NULL);

	if (!_hWnd) return S_FALSE;

	// 생성된 윈도를 화면에 표시
	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);

	// 디버깅, 테스트용 콘솔을 생성
 	AllocConsole();
	FILE* _tempFile;
	freopen_s(&_tempFile, "CONOUT$", "w", stdout);
		
	_deltatime = 0;
	_timer = new Timer();
	
	_gameprocess = new GameProcess();
	_gameprocess->Initialize();

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
