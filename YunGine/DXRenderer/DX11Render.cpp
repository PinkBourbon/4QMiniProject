#include "DX11Render.h"
#include <iostream>
#include <fstream>

#include <d3dcompiler.h>
#include <d3dcommon.h>

#include "Axis.h"
#include "Cube.h"
#include "Grid.h"
#include "Camera.h"

// dll�� �θ��� �������� ����� �Լ��� �ּҸ� ������ �ִ´�.
// return�� �����ͷ� �޾��� �� �ִ�.
IDX11Render* CreateRenderer()
{
	return new DX11Render();
}

// dll�� �������� ����� �Լ�
// �Լ��� �ּҸ� �����ϸ� �ȴ�.
void DeleteRenderer(IDX11Render* instance)
{
	delete instance;
}

DX11Render::DX11Render()
	: VertexBuffer(nullptr),
	IndexBuffer(nullptr),
	m_pAxis(nullptr),
	m_WorldMatrix
	{ 1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f },
	m_ViewMatrix(),
	m_ProjectionMatrix()
{

}

DX11Render::~DX11Render()
{

}

long DX11Render::Initialize(void* hwnd)
{
	HRESULT hr = S_OK;

	hr = CreateDevice();
	if (FAILED(hr))
	{
		return false;
		// ��ġ �������̽� ���� ���а� �߻��� ��� �̸� ó���մϴ�.
		// ���� ���, ��� ���� �䱸 ������ ���̰ų� ���Ͽ��� 
		// ���� ������.
	}

	hr = CreateSwapChain((HWND)hwnd);	// ����ü�� ����
	if (FAILED(hr))
	{
		return false;
	}

	hr = CreateBackBuffer();
	if (FAILED(hr))
	{
		return false;
	}

	hr = CreateRaster();
	if (FAILED(hr))
	{
		return false;
	}

	hr = CreateObject();	// ������Ʈ���� ��� ���⼭ �����.
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void DX11Render::Update(float deltaTime)
{
	 m_deltaTime = deltaTime;
	 
	 // ī�޶�
	 if (GetAsyncKeyState('W') & 0x8000)
	 	m_pCamera->Walk(10.0f * deltaTime);
	 
	 if (GetAsyncKeyState('S') & 0x8000)
	 	m_pCamera->Walk(-10.0f * deltaTime);
	 
	 if (GetAsyncKeyState('A') & 0x8000)
	 	m_pCamera->Strafe(-10.0f * deltaTime);
	 
	 if (GetAsyncKeyState('D') & 0x8000)
	 	m_pCamera->Strafe(10.0f * deltaTime);
	 
	 if (GetAsyncKeyState('Q') & 0x8000)
	 	m_pCamera->WorldUpDown(-10.0f * deltaTime);
	 
	 if (GetAsyncKeyState('E') & 0x8000)
	 	m_pCamera->WorldUpDown(10.0f * deltaTime);
	 
	 m_pCamera->UpdateViewMatrix();

	 m_pAxis->ObjectUpdate(DirectX::XMMatrixIdentity(), m_pCamera->View(), m_pCamera->Proj());
	 m_pGrid->ObjectUpdate(DirectX::XMMatrixIdentity(), m_pCamera->View(), m_pCamera->Proj());
	 m_pCube->ObjectUpdate(DirectX::XMMatrixIdentity(), m_pCamera->View(), m_pCamera->Proj());

// 	m_pAxis->ObjectUpdate(DirectX::XMMatrixIdentity(), view,proj);
// 	m_pGrid->ObjectUpdate(DirectX::XMMatrixIdentity(), view,proj);
// 	m_pCube->ObjectUpdate(DirectX::XMMatrixIdentity(), view,proj);



}

void DX11Render::Render()
{
	// �� �ȿ��ٰ� ��䷻��, ��ο������Ʈ, ���巻���� �ִ°� ȿ�����ΰ�?
	// 
}

void DX11Render::BeginRender(float red, float green, float blue, float alpha)
{
	float color[4];

	// Setup the color to clear the buffer to.
	color[0] = red;	// r
	color[1] = green;	// g
	color[2] = blue;	// b
	color[3] = alpha;	// a

	m_p3DDeviceContext->OMSetRenderTargets(
		1,
		m_pRenderTargetView.GetAddressOf(),
		m_pDepthStencilView.Get()
	);

	// Clear the back buffer.
	m_p3DDeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), color);
	// Clear the depth buffer.
	m_p3DDeviceContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	//d3dDeviceContext_->OMSetRenderTargets(1, renderTargetView_.GetAddressOf(), depthStencilView_.Get());

}

void DX11Render::DrawObject()
{
	DirectX::XMMATRIX worldMatrix = XMLoadFloat4x4(&m_WorldMatrix);
	DirectX::XMMATRIX viewMatrix = XMLoadFloat4x4(&m_ViewMatrix);
	DirectX::XMMATRIX projMatrix = XMLoadFloat4x4(&m_ProjectionMatrix);

	m_p3DDeviceContext->OMSetDepthStencilState(m_pDepthStencilState.Get(), 0);

	m_pAxis->Render();
	m_pGrid->Render();
	m_pCube->Render();

	// �����Ͷ����� ���� ���� 
	m_p3DDeviceContext->RSSetState(0);
}

void DX11Render::EndRender()
{
	sm_SwapChain->Present(1, 0);

	return;
}

HRESULT DX11Render::InitVB()
{
	return S_OK;
}

void DX11Render::Finalize()
{
	
}

HRESULT DX11Render::CreateDevice()
{
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	D3D_FEATURE_LEVEL FeatureLevels = D3D_FEATURE_LEVEL_11_1;

	UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(DEBUG) || defined(_DEBUG)
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr = D3D11CreateDevice(
		nullptr,                    // �⺻ ����͸� ����Ϸ��� nullptr�� �����Ͻʽÿ�.
		D3D_DRIVER_TYPE_HARDWARE,   // �ϵ���� �׷��� ����̹��� ����Ͽ� ��ġ�� �����մϴ�.
		nullptr,                       // ����̹��� D3D_DRIVER_TYPE_SOFTWARE�� �ƴ� �� 0�̾�� �մϴ�.
		deviceFlags,                // ����� �� Direct2D ȣȯ�� �÷��׸� �����մϴ�.
		levels,                     // �� ���� ������ �� �ִ� ��� ���� ����Դϴ�.
		ARRAYSIZE(levels),          // �� ����� ũ���Դϴ�.
		D3D11_SDK_VERSION,          // Windows Store ���� ��� �׻� D3D11_SDK_VERSION���� �����Ͻʽÿ�.
		&m_p3DDevice,   // ������ Direct3D ��ġ�� ��ȯ�մϴ�.
		&FeatureLevels,             // ������ ����̽��� ���� ������ ��ȯ�մϴ�.
		&m_p3DDeviceContext			        // ��ġ ��� ���ؽ�Ʈ�� ��ȯ�մϴ�.
	);

	return hr;
}

HRESULT DX11Render::CreateSwapChain(HWND hWnd)
{
	HRESULT hr = S_OK;

	Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
	Microsoft::WRL::ComPtr<IDXGIFactory> factory;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.Windowed = TRUE; // Sets the initial state of full-screen mode.
	desc.BufferCount = 2;
	desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.SampleDesc.Count = 1;      //multisampling setting
	desc.SampleDesc.Quality = 0;    //vendor-specific flag
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	desc.OutputWindow = hWnd;

	m_p3DDevice.As(&dxgiDevice);

	hr = dxgiDevice->GetAdapter(&adapter);

	if (SUCCEEDED(hr))
	{
		adapter->GetParent(IID_PPV_ARGS(&factory));

		hr = factory->CreateSwapChain(
			m_p3DDevice.Get(),
			&desc,
			&sm_SwapChain
		);
	}

	return hr;
}

HRESULT DX11Render::CreateBackBuffer()
{
	HRESULT hr;

	// ����� �����
	//====================================
	D3D11_TEXTURE2D_DESC m_BackBufferDesc;

	hr = sm_SwapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		(void**)(m_pBackBuffer.GetAddressOf()));

	hr = m_p3DDevice->CreateRenderTargetView(
		m_pBackBuffer.Get(),
		nullptr,
		m_pRenderTargetView.GetAddressOf()
	);

	m_pBackBuffer->GetDesc(&m_BackBufferDesc);	// Desc ������? -> ����ۿ����� �������� ����ִ� ����ü


	// ���� ���Ľ�
	// 3D�� ���� �����Ҷ� �ʿ���
	//======================================

	CD3D11_TEXTURE2D_DESC depthStencilDesc(
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		static_cast<UINT> (m_BackBufferDesc.Width),
		static_cast<UINT> (m_BackBufferDesc.Height),
		1, // This depth stencil view has only one texture.
		1, // Use a single mipmap level.
		D3D11_BIND_DEPTH_STENCIL
	);

	m_p3DDevice->CreateTexture2D(
		&depthStencilDesc,
		nullptr,
		&m_pTexture2D
	);

	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);

	m_p3DDevice->CreateDepthStencilView(
		m_pTexture2D.Get(),
		&depthStencilViewDesc,
		&m_pDepthStencilView
	);

	//����Ʈ
	//=================================================

	D3D11_VIEWPORT m_ViewPort;
	ZeroMemory(&m_ViewPort, sizeof(D3D11_VIEWPORT));
	m_ViewPort.Height = (float)m_BackBufferDesc.Height;
	m_ViewPort.Width = (float)m_BackBufferDesc.Width;
	m_ViewPort.MinDepth = 0;
	m_ViewPort.MaxDepth = 1;

	m_p3DDeviceContext->RSSetViewports(
		1,
		&m_ViewPort
	);

	return hr;
}

HRESULT DX11Render::CreateRaster()
{
	HRESULT hr = S_OK;

	// ������
	//=================================================

	D3D11_RASTERIZER_DESC solidRasterDesc;	// ä��� ���
	ZeroMemory(&solidRasterDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidRasterDesc.FillMode = D3D11_FILL_SOLID;	// ä��� ���
	solidRasterDesc.CullMode = D3D11_CULL_BACK;		// Back�� �׸��� ����
	solidRasterDesc.FrontCounterClockwise = false;	// �ݽðԸ� false = �ð�������� �׸��ڴٴ� ���̴�.
	solidRasterDesc.DepthClipEnable = true;			// �Ÿ��� ���� Ŭ������ ����

	hr = m_p3DDevice->CreateRasterizerState
	(
		&solidRasterDesc,
		m_pSolidRasterState.GetAddressOf()
	);


	//=================================================

	D3D11_RASTERIZER_DESC wireRasterDesc;	// ä��������-> �����׸�
	ZeroMemory(&wireRasterDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireRasterDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireRasterDesc.CullMode = D3D11_CULL_NONE;
	wireRasterDesc.FrontCounterClockwise = false;
	wireRasterDesc.DepthClipEnable = true;

	hr = m_p3DDevice->CreateRasterizerState
	(
		&wireRasterDesc,
		m_pWireRasterState.GetAddressOf()
	);

	//====================================================

	return hr;
}

HRESULT DX11Render::CreateObject()
{
	HRESULT hr = S_OK;

	hr = CreateCamera();
	if (FAILED(hr))
	{
		return hr;
	}

	hr = CreateAxis();
	if (FAILED(hr))
	{
		return hr;
	}

	hr = CreateGrid();
	if (FAILED(hr))
	{
		return hr;
	}

	hr = CreateCube();
	if (FAILED(hr))
	{
		return hr;
	}

	return hr;
}

HRESULT DX11Render::CreateCamera()
{
	HRESULT hr = S_OK;

	m_pCamera = new Camera();
 
	// ī�޶� �����
	// ������ ���ش�.
	 m_pCamera->SetLens(0.25f * 3.1415926535f, 1280.0f / 720.0f, 1.0f,1000.0f);

	 // LH(Left Hand)��������
	 DirectX::XMMATRIX p = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60.0f), 1280.0f / 720.0f, 1.0f, 1000.0f);
	 DirectX::XMStoreFloat4x4(&m_ProjectionMatrix, p);

	 // ��ó���� ���� ī�޶��� ������, �Ĵٺ��� ����,UP���� ���ϱ�
	 m_pCamera->LookAt(DirectX::XMFLOAT3(8.0f, 8.0f, -8.0f), DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 1.0f, 0));

	return S_OK;
}

HRESULT DX11Render::CreateCube()
{
	HRESULT hr = S_OK;

	m_pCube = new Cube(m_p3DDevice, m_p3DDeviceContext, m_pWireRasterState);

	return S_OK;
}

HRESULT DX11Render::CreateGrid()
{
	HRESULT hr = S_OK;

	m_pGrid = new Grid(m_p3DDevice, m_p3DDeviceContext, m_pWireRasterState);

	return S_OK;
}

HRESULT DX11Render::CreateAxis()
{
	HRESULT hr = S_OK;

	m_pAxis = new Axis(m_p3DDevice, m_p3DDeviceContext, m_pWireRasterState);

	return S_OK;
}