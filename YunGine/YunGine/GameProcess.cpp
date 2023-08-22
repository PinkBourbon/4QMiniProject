#include "GameProcess.h"

GameProcess::~GameProcess()
{

}

HRESULT GameProcess::MyInitialize(HINSTANCE hInstance)
{
	
	if (CreateGraphicEngine() == S_FALSE)
	{
		return S_FALSE;
	}

	// 오브젝트 등록
	::RegisterObject(testCube.renderable);
	::RegisterObject(testCube1.renderable);
	::RegisterObject(testCube2.renderable);
	::RegisterObject(testCube3.renderable);
	::RegisterObject(testCube4.renderable);

	testCube1.transform.SetPosition(1.0f, 2.0f, 3.0f);
	testCube2.transform.SetPosition(2.0f, 4.0f, 6.0f);
	testCube3.transform.SetPosition(3.0f, 6.0f, 9.0f);
	testCube4.transform.SetPosition(4.0f, 8.0f, 10.0f);

	// 테스팅
	::RegisterObject(myTest.renderable);
	myTest.transform.SetPosition(0.0f, 0.0f, 0.0f);


	// 지우기
	::DeregisterObject(testCube.renderable);

	_timer = new GameTimer();
	_timer->Reset();

	return S_OK;
}

void GameProcess::Loop()
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
			// Y축 기준 회전
			testCube1.transform.AddRotation({ 0.0f, 1.0f, 0.0f }, 1.0f);

			Update();
			Render();
		}

	}
}

void GameProcess::Update()
{

	// 매 프레임 시간을 계산한다.
	_timer->Tick();

	// 매 프레임의 deltaTime
	_timer->DeltaTime();

	// 키 입력
	if (GetAsyncKeyState(VK_RETURN))
	{

	}

	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	/// 타이머를 기반으로 FPS, millisecond per frame (1프레임당 elapsedTime = deltaTime)을 계산 해 준다.

	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;


	if ((_timer->TotalTime() - timeElapsed) >= 1.0f)
	{
		// FPS 계산: 현재까지 누적된 프레임 수를 1초 동안의 시간으로 나누어 계산합니다.
		float fps = (float)frameCnt; // fps = frameCnt / 1

		// MSPF 계산: FPS를 이용하여 1초당 평균 프레임 시간(Milliseconds per Frame)을 계산합니다.
		float mspf = 1000.0f / fps;

		// Reset for next average.
		// 1초 동안의 평균 계산이 완료되면, 다음 1초간의 계산을 위해 누적된 프레임 수와 시간을 초기화합니다.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}

	// 일단 대충 해놓음->랜더 update에 float deltatime을 넣음
	//_renderer->Update(_timer->DeltaTime());
}

void GameProcess::Render()
{
	/// 그리기를 준비한다.
	// 그래픽엔진을 아직 붙이지 않았다.
	//renderer->BeginRender(0, 0, 0, 1);
	//
	//renderer->DrawObject();
	//
	///// 그리기를 끝낸다.
	//renderer->EndRender();

	//_renderer->Render();
	::Render(_timer->DeltaTime());
}

HRESULT GameProcess::CreateGraphicEngine()
{
	// dll을 직접적으로 가져오기로 결정
	//HMODULE Module = LoadLibrary(RENDER_PATH);
	//_hModule = Module;
	//if (_hModule == nullptr)	// dll 로드 실패
	//{
	//	return S_FALSE;
	//}
	//
	//_renderer.reset(reinterpret_cast<IDX11Render * (*)(void)>(GetProcAddress(_hModule, "CreateRenderer"))());
	//
	//// using CreateRenderer = IDX11Render(*)();
	//
	//// CreateRenderer createRenderer = reinterpret_cast<CreateRenderer>(GetProcAddress(m_hModule, "CreateRenderer"));
	//if (_renderer == nullptr)
	//{
	//	// 함수 가져오기 실패 처리
	//	FreeLibrary(_hModule);
	//	return S_FALSE;
	//}
	//else
	//{
	//	// 구체적인 내부 구현이 없으므로 사용할 수 없는 것이다.
	//	_renderer->Initialize();
	//}
	bool succes = ::Initialize();
	//_renderer.reset(CreateRenderer());

	return S_OK;
}

HRESULT GameProcess::DeleteGraphicEngine()
{
	// unique_ptr이라서 굳이 명시적으로 해제하지 않아도 될꺼같아
	//_renderer->Finalize();
	// typedef void (*DeleteRendererFunc)(IDX11Render*);
	// DeleteRendererFunc deleteRenderer = reinterpret_cast<DeleteRendererFunc>(GetProcAddress(m_hModule, "DeleteRenderer"));
	//_renderer.release();

	//FreeLibrary(_hModule);

	::Finalize();

	return S_OK;
}

void GameProcess::Finalize()
{
	// 그래픽엔진을 파이널라이즈에서 해제한다.
	DeleteGraphicEngine();
}

LRESULT CALLBACK GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
