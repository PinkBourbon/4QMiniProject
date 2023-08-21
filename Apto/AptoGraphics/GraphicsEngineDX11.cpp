module;
#include <windows.h>
#include <d3d11_4.h>
//#include <dxgi1_6.h>
#include <DirectXColors.h>

#if defined(DEBUG) || defined(_DEBUG)
#include <dxgidebug.h>
#endif

#include <wrl/client.h>
#include <vector>
#include <string>

#include "AptoMacro.h"
#include "ResourceMgr.h"
#include "RenderableObject.h"

#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "D3D11.lib")
module aptoCore.Graphics;

#ifndef USE_DX12
namespace aptoCore::Graphics
{
	template<typename T>
	using comptr = Microsoft::WRL::ComPtr<T>;

	__declspec(thread) HWND g_hwnd;

	// 엔진 상태등에 관련된 변수들
	__declspec(thread) bool g_isRunRenderEngine;
	__declspec(thread) bool g_useVsync;
	__declspec(thread) UINT g_monitorIndex = 0;
	__declspec(thread) UINT g_refreshRatesIndex = 1;

	// 모니터 관련 변수들
	__declspec(thread) unsigned __int32 g_displayWidth = 1280;
	__declspec(thread) unsigned __int32 g_displayHeight = 720;
	__declspec(thread) std::vector<std::vector<DXGI_RATIONAL>> g_displayRefreshRates;

	// D3D11 관련 해제해야 하는 변수들
	__declspec(thread) comptr<ID3D11Device> g_device;
	__declspec(thread) comptr<ID3D11DeviceContext> g_immediateContext;
	__declspec(thread) comptr<IDXGIFactory2> g_dxgiFactory;
	__declspec(thread) std::vector<comptr<IDXGIAdapter1>> g_adapters;
	__declspec(thread) std::vector<comptr<IDXGIOutput1>> g_outputs;
	__declspec(thread) comptr<IDXGISwapChain1> g_swapChain;
	__declspec(thread) comptr<ID3D11Texture2D> g_backBuffer;
	__declspec(thread) comptr<ID3D11Texture2D> g_depthStencil;
	__declspec(thread) comptr<ID3D11RenderTargetView> g_renderTargetView;
	__declspec(thread) comptr<ID3D11DepthStencilView> g_depthStencilView;
	__declspec(thread) comptr<ID3D11RasterizerState> g_rasterizerState;

	// 화면을 그리기 위해 renderAbleObject를 관리하는	변수
	__declspec(thread) std::vector<RenderableObject> g_renderAbleObjects;

	// Resource 관련 변수들
	// __declspec(thread) 

	bool Initialize()
{
		g_hwnd = InitializeWindow(g_displayWidth, g_displayHeight);

		D3D_FEATURE_LEVEL maxSupportedFeatureLevel = D3D_FEATURE_LEVEL_9_1;

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG) || defined(_DEBUG)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		HRESULT result = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			creationFlags,
			featureLevels,
			ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION,
			&g_device,
			&maxSupportedFeatureLevel,
			&g_immediateContext
		);

		if (result != S_OK)
		{
			APTO_ASSERT(false, "Device 생성 실패");
			return false;
		}

		UINT numQualityLevels = 0;
		result = g_device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &numQualityLevels);

		if (result != S_OK)
		{
			APTO_ASSERT(false, "멀티 샘플 품질레벨 체크 실패");
			return false;
		}

		result = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, __uuidof(IDXGIFactory2), (void**)(&g_dxgiFactory));

		if (result != S_OK)
		{
			APTO_ASSERT(false, "DXGI Factory 생성 실패");
			return false;
		}

		if (!InitDisplayInfo())
		{
			APTO_ASSERT(false, "모니터 모드 초기화 실패");
			return false;
		}

		if (!InitGPUInfo())
		{
			APTO_ASSERT(false, "GPU 정보 초기화 실패");
			return false;
		}

		DXGI_SWAP_CHAIN_DESC1 desc = { 0, };

		desc.Width = 0; // CreateSwapChainForHwnd 로 호출 시 0으로 세팅하면 해당 hwnd에서 런타임에 출력창에서 너비를 가져옵니다.
		desc.Height = 0; // CreateSwapChainForHwnd 로 호출 시 0으로 세팅하면 해당 hwnd에서 런타임에 출력창에서 높이를 가져옵니다.
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.Stereo = FALSE;
		desc.SampleDesc = { 1, 0 };
		desc.BufferUsage = DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 2;
		desc.Scaling = DXGI_SCALING_STRETCH;
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullScreenDesc = { };
		fullScreenDesc.RefreshRate = { 0, 0 };
		fullScreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST;
		fullScreenDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
		fullScreenDesc.Windowed = true;

		result = g_dxgiFactory->CreateSwapChainForHwnd(g_device.Get(), g_hwnd, &desc, &fullScreenDesc, NULL, &g_swapChain);

		if (result != S_OK)
		{
			APTO_ASSERT(false, "스왑체인 생성 실패");
			return false;
		}

		OnResize();
		//if (!Resize(1280, 720))
		//{
		//	ASSERT(false, "화면 사이즈 변경 실패");
		//	return false;
		//}

		D3D11_RASTERIZER_DESC rasterizerDesc = { };
		rasterizerDesc.AntialiasedLineEnable = false;
		rasterizerDesc.CullMode = D3D11_CULL_BACK;
		rasterizerDesc.DepthBias = 0;
		rasterizerDesc.DepthBiasClamp = 0.0f;
		rasterizerDesc.DepthClipEnable = true;
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.FrontCounterClockwise = false;
		rasterizerDesc.MultisampleEnable = false;
		rasterizerDesc.ScissorEnable = false;
		rasterizerDesc.SlopeScaledDepthBias = 0.0f;

		result = g_device->CreateRasterizerState(&rasterizerDesc, &g_rasterizerState);
		if (result != S_OK)
		{
			APTO_ASSERT(false, "RasterizerState 생성 실패");
			return false;
		}

		g_immediateContext->RSSetState(g_rasterizerState.Get());

		g_isRunRenderEngine = true;
		return true;
	}

	void Finalize()
	{
		g_device = nullptr;
		g_immediateContext = nullptr;
		g_dxgiFactory = nullptr;
		g_swapChain = nullptr;
		g_backBuffer = nullptr;
		g_depthStencil = nullptr;
		g_renderTargetView = nullptr;
		g_depthStencilView = nullptr;
		g_rasterizerState = nullptr;

		for (auto& adapter : g_adapters)
		{
			adapter = nullptr;
		}
		g_adapters.clear();

		for (auto& output : g_outputs)
		{
			output = nullptr;
		}
		g_outputs.clear();

		g_isRunRenderEngine = false;
	}

	void Render(float deltaTime)
{
		// 렌더링 하기 전 모든 윈도우 메세지를 처리하자.
		MSG msg;
		msg.message = WM_NULL;

		while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// 윈도우 창이 종료됐다면 렌더링 할 필요가 없으니 즉시 return
			if (msg.message == WM_QUIT)
			{
				g_isRunRenderEngine = false;
				return;
			}
		}

		// 렌더링을 시작하기 위해 초기화
		g_immediateContext->ClearRenderTargetView(g_renderTargetView.Get(), DirectX::Colors::Black);
		g_immediateContext->ClearDepthStencilView(g_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		//g_immediateContext->OMSetRenderTargets(1, g_renderTargetView.GetAddressOf(), g_depthStencilView.Get());



		// 수직동기화 여부에 따라서 present
		if (g_useVsync)
		{
			g_swapChain->Present(1, 0);
		}
		else
		{
			g_swapChain->Present(0, 0);
		}
	}

	bool Resize(unsigned __int32 screenWidth, unsigned __int32 screenHeight)
	{
		if (!g_swapChain)
		{
			return false;
		}

		DXGI_MODE_DESC desc = { 0, };
		desc.Width = screenWidth;
		desc.Height = screenHeight;
		if (g_useVsync)
		{
			// 일단은 임시로 세팅해 놓자.
			desc.RefreshRate.Numerator = g_displayRefreshRates[g_monitorIndex][g_refreshRatesIndex].Numerator;
			desc.RefreshRate.Denominator = g_displayRefreshRates[g_monitorIndex][g_refreshRatesIndex].Denominator;
		}
		else
		{
			desc.RefreshRate.Numerator = 0;
			desc.RefreshRate.Denominator = 1;
		}

		desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		g_swapChain->ResizeTarget(&desc);

		OnResize();

		g_displayWidth = screenHeight;
		g_displayHeight = screenHeight;
		return true;
	}

	void RegisterObject(Renderable& object)
	{
		//RenderableObject newObject;
		//Mesh* mesh = ;

	}

	void DeregisterObject(Renderable& object)
	{
	}

	bool isRunEngine()
	{
		return g_isRunRenderEngine;
	}
}


static LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_SIZE:
			aptoCore::Graphics::OnResize();
			//aptoCore::Graphics::Resize(LOWORD(lParam), HIWORD(lParam));
			return 0;
		case WM_DESTROY:
			::PostQuitMessage(0);
			return 0;
	}

	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

namespace aptoCore::Graphics
{
	HWND InitializeWindow(int windowWidth, int windowHeight)
	{
		WNDCLASSEX wc
		{
			sizeof(WNDCLASSEX),		// cbSize
			CS_CLASSDC,				// style
			WndProc,				// lpfnWndProc
			0L,						// cbClsExtra
			0L,						// cbWndExtra
			GetModuleHandle(NULL),	// hInstance
			NULL,					// hIcon
			NULL,					// hCursor
			NULL,					// hbrBackground
			NULL,					// lpszMenuName
			L"AptoEngine",			// lpszClassName
			NULL					// hIconSm
		};

		RegisterClassEx(&wc);

		RECT windowRect = { 0, 0, windowWidth, windowHeight };    // 윈도우 창 크기
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

		HWND hwnd = CreateWindow
		(
			wc.lpszClassName,
			L"GlassEngine",
			WS_OVERLAPPEDWINDOW | WS_SIZEBOX,
			100, // 윈도우 좌측 상단의 x 좌표
			100, // 윈도우 좌측 상단의 y 좌표
			windowRect.right - windowRect.left, // 윈도우 가로 방향 해상도
			windowRect.bottom - windowRect.top, // 윈도우 세로 방향 해상도
			NULL,
			NULL,
			wc.hInstance,
			NULL
		);

		ShowWindow(hwnd, SW_SHOWDEFAULT);
		UpdateWindow(hwnd);

		return hwnd;
	}

	bool InitDisplayInfo()
	{
		if (g_dxgiFactory == nullptr)
		{
			APTO_ASSERT(false, "dxgiFactory 부터 만드세요");
			return false;
		}

		IDXGIAdapter1* adapter = nullptr;
		for (int i = 0; g_dxgiFactory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
		{
			g_adapters.emplace_back(adapter);
			adapter->Release();
		}

		IDXGIOutput1* output = nullptr;
		for (int i = 0; g_adapters[0]->EnumOutputs(i, (IDXGIOutput**)&output) != DXGI_ERROR_NOT_FOUND; ++i)
		{
			g_outputs.emplace_back(output);
			output->Release();
		}

		g_displayRefreshRates.resize(g_outputs.size());

		for (int i = 0; i < g_outputs.size(); ++i)
		{
			unsigned __int32 displayModeNum = 0;
			HRESULT result = g_outputs[i]->GetDisplayModeList1(DXGI_FORMAT_R8G8B8A8_UNORM, 0, &displayModeNum, NULL);
			if (result != S_OK)
			{
				APTO_ASSERT(false, "디스플레이 모드 리스트 갯수 가져오기 실패");
				return false;
			}

			std::unique_ptr<DXGI_MODE_DESC1[]> dxgiModeArr(new DXGI_MODE_DESC1[displayModeNum]);
			
			if(dxgiModeArr.get() == nullptr)
			{
				APTO_ASSERT(false, "디스플레이 모드 리스트 할당 실패");
				return false;
			}

			result = g_outputs[i]->GetDisplayModeList1(DXGI_FORMAT_R8G8B8A8_UNORM, 0, &displayModeNum, dxgiModeArr.get());
			if (result != S_OK)
			{
				return false;
			}

			for (unsigned int j = 0; j < displayModeNum; ++j)
			{
				if (dxgiModeArr.get()[j].Width == g_displayWidth
					&& dxgiModeArr.get()[j].Height == g_displayHeight)
				{
					g_displayRefreshRates[i].emplace_back(dxgiModeArr.get()[j].RefreshRate);
				}
			}
		}

		return true;
	}

	bool InitGPUInfo()
	{
		if (g_adapters.empty())
		{
			APTO_ASSERT(false, "디스플레이 모드를 먼저 초기화 해주세요");
			return false;
		}

		for (int i = 0; i < g_adapters.size(); ++i)
		{
			DXGI_ADAPTER_DESC1 adapterDesc;
			g_adapters[i]->GetDesc1(&adapterDesc);

			SIZE_T gpuMemoryMB = adapterDesc.DedicatedVideoMemory / 1024 / 1024;
			std::wstring gpuName = adapterDesc.Description;
		}

		return true;
	}

	bool OnResize()
	{
		if (!g_immediateContext)
		{
			return false;
		}

		g_immediateContext->OMSetRenderTargets(0, nullptr, nullptr);

		g_renderTargetView = nullptr;
		g_depthStencilView = nullptr;
		g_depthStencil = nullptr;
		g_backBuffer = nullptr;
		
		HRESULT result = g_swapChain->ResizeBuffers(2, 0, 0, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING);
		if (result != S_OK)
		{
			APTO_ASSERT(false, "스왑체인 리사이즈 실패");
			return false;
		}

		result = g_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)(&g_backBuffer));

		if (result != S_OK)
		{
			APTO_ASSERT(false, "버퍼 가져오기 실패");
			return false;
		}

		result = g_device->CreateRenderTargetView(g_backBuffer.Get(), nullptr, &g_renderTargetView);

		if (result != S_OK)
		{
			APTO_ASSERT(false, "렌더 타겟 뷰 생성 실패");
			return false;
		}

		D3D11_TEXTURE2D_DESC backBufferDesc = { 0 };
		g_backBuffer->GetDesc(&backBufferDesc);

		// 뎁스 스텐실 뷰 만들기
		CD3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.Width = backBufferDesc.Width;
		depthStencilDesc.Height = backBufferDesc.Height;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		g_device->CreateTexture2D(&depthStencilDesc, nullptr, &g_depthStencil);

		g_device->CreateDepthStencilView(g_depthStencil.Get(), nullptr, &g_depthStencilView);

		g_immediateContext->OMSetRenderTargets(1, g_renderTargetView.GetAddressOf(), g_depthStencilView.Get());

		// 뷰포트 생성
		D3D11_VIEWPORT viewPort[1];
		viewPort[0].TopLeftX = 0.0f;
		viewPort[0].TopLeftY = 0.0f;
		viewPort[0].Width = (FLOAT)backBufferDesc.Width;
		viewPort[0].Height = (FLOAT)backBufferDesc.Height;
		viewPort[0].MinDepth = 0.0f;
		viewPort[0].MaxDepth = 1.0f;

		g_immediateContext->RSSetViewports(1, viewPort);

		g_displayWidth = backBufferDesc.Width;
		g_displayHeight = backBufferDesc.Height;

		// 테스트를 위한 배경 색상 변경
		float bgColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
		g_immediateContext->ClearRenderTargetView(g_renderTargetView.Get(), bgColor);

		return true;
	}
}

#endif
