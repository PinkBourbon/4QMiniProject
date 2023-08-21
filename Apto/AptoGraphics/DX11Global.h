#pragma once

#include <wrl/client.h>
#include <d3d11.h>
#include <vector>
#include <dxgi1_4.h>

template<typename T>
using comptr = Microsoft::WRL::ComPtr<T>;

extern comptr<ID3D11Device> g_device;
extern comptr<ID3D11DeviceContext> g_immediateContext;
extern comptr<IDXGIFactory2> g_dxgiFactory;
extern std::vector<comptr<IDXGIAdapter1>> g_adapters;
extern std::vector<comptr<IDXGIOutput1>> g_outputs;
extern comptr<IDXGISwapChain1> g_swapChain;
extern comptr<ID3D11Texture2D> g_backBuffer;
extern comptr<ID3D11Texture2D> g_depthStencil;
extern comptr<ID3D11RenderTargetView> g_renderTargetView;
extern comptr<ID3D11DepthStencilView> g_depthStencilView;
extern comptr<ID3D11RasterizerState> g_rasterizerState;
