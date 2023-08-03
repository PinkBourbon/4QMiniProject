#include "GameProcess.h"

GameProcess::~GameProcess()
{

}

HRESULT GameProcess::Initialize(HINSTANCE hInstance)
{
	/// Win32 ����
	// ���� Ŭ����
	// 
	// ��Ƽ����Ʈ���� �����ڵ�� �Ѿ���鼭 char* ������ ���µ�
	// �̷������� ����ȯ�� �ص� �ɱ�?
	wchar_t szAppName[] = L"YJD3Ddemo Engine";
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = GameProcess::WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	// ���� Ŭ���� ���
	RegisterClass(&wndclass);

	// ���� ����
	hWnd = CreateWindow(
		// ��Ƽ����Ʈ���� �����ڵ�� �Ѿ���鼭 char* ������ ���µ�
		// �̷������� ����ȯ�� �ص� �ɱ�?
		szAppName,
		szAppName,
		WS_OVERLAPPEDWINDOW,
		100, 100, m_ScreenWidth, m_ScreenHeight,
		NULL, NULL, hInstance, NULL);

	if (!hWnd) return S_FALSE;

	// ������ ������ ȭ�鿡 ǥ��
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	if (CreateGraphicEngine() == S_FALSE)
	{
		return S_FALSE;
	}

	m_pTimer = new GameTimer();
	m_pTimer->Reset();


	return S_OK;
}

void GameProcess::Loop()
{
	while (true)
	{
		if (PeekMessage(&m_Msg, NULL, 0, 0, PM_REMOVE))
		{
			if (m_Msg.message == WM_QUIT) break;

			DispatchMessage(&m_Msg);
		}
		else
		{
			Update();
			Render();
		}

	}
	}


void GameProcess::Update()
{

	// �� ������ �ð��� ����Ѵ�.
	m_pTimer->Tick();

	// �� �������� deltaTime
	m_pTimer->DeltaTime();

	// Ű �Է�
	if (GetAsyncKeyState(VK_RETURN))
	{

	}

	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	/// Ÿ�̸Ӹ� ������� FPS, millisecond per frame (1�����Ӵ� elapsedTime = deltaTime)�� ��� �� �ش�.

	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;


	if ((m_pTimer->TotalTime() - timeElapsed) >= 1.0f)
	{
		// FPS ���: ������� ������ ������ ���� 1�� ������ �ð����� ������ ����մϴ�.
		float fps = (float)frameCnt; // fps = frameCnt / 1

		// MSPF ���: FPS�� �̿��Ͽ� 1�ʴ� ��� ������ �ð�(Milliseconds per Frame)�� ����մϴ�.
		float mspf = 1000.0f / fps;

		// Reset for next average.
		// 1�� ������ ��� ����� �Ϸ�Ǹ�, ���� 1�ʰ��� ����� ���� ������ ������ ���� �ð��� �ʱ�ȭ�մϴ�.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}

	// �ϴ� ���� �س���->���� update�� float deltatime�� ����
	renderer->Update(m_pTimer->DeltaTime());
}

void GameProcess::Render()
{
	/// �׸��⸦ �غ��Ѵ�.
	// �׷��ȿ����� ���� ������ �ʾҴ�.
	renderer->BeginRender(0, 0, 0, 1);

	renderer->DrawObject();

	/// �׸��⸦ ������.
	renderer->EndRender();
}

HRESULT GameProcess::CreateGraphicEngine()
{
	// dll�� ���������� ��������� ����
	HMODULE Module = LoadLibrary(RENDER_PATH);
	m_hModule = Module;
	if (m_hModule == nullptr)	// dll �ε� ����
	{
		return S_FALSE;
	}

	renderer.reset(reinterpret_cast<IDX11Render * (*)(void)>(GetProcAddress(m_hModule, "CreateRenderer"))());

	// using CreateRenderer = IDX11Render(*)();

	// CreateRenderer createRenderer = reinterpret_cast<CreateRenderer>(GetProcAddress(m_hModule, "CreateRenderer"));
	if (renderer == nullptr)
	{
		// �Լ� �������� ���� ó��
		FreeLibrary(m_hModule);
		return S_FALSE;
	}
	else
	{
		// ��ü���� ���� ������ �����Ƿ� ����� �� ���� ���̴�.
		renderer->Initialize((void*)hWnd);
	}

	return S_OK;
}

HRESULT GameProcess::DeleteGraphicEngine()
{
	// unique_ptr�̶� ���� ���������� �������� �ʾƵ� �ɲ�����
	renderer->Finalize();
	// typedef void (*DeleteRendererFunc)(IDX11Render*);
	// DeleteRendererFunc deleteRenderer = reinterpret_cast<DeleteRendererFunc>(GetProcAddress(m_hModule, "DeleteRenderer"));
	renderer.release();

	FreeLibrary(m_hModule);
	
	return S_OK;
}

void GameProcess::Finalize()
{
	// �׷��ȿ����� ���̳ζ������ �����Ѵ�.
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