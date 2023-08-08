#pragma once
#include <windows.h>
#include "Timer.h"

class GameProcess;

class MainProcess
{
public:
	HRESULT Initialize(HINSTANCE hInstance);
	void Loop();
	void Finalize();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	HWND _hWnd;
	MSG _msg;
	HINSTANCE _hInstance;
	HANDLE _consoleHandle;

	//게임엔진
	GameProcess* _gameprocess;

	// 시간과 관련된 부분
	Timer* _timer;
	double _deltatime;

};

