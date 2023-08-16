#include "Axis.h"

Axis::Axis(
	Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, 
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pDeviceContext, 
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>& pRasterState)	// wireRaster로 받음
{
	pDevice.CopyTo(_3DDevice.GetAddressOf());
	pDeviceContext.CopyTo(_3DDeviceContext.GetAddressOf());
	pRasterState.CopyTo(_RasterState.GetAddressOf());

	ObjectSetting();
}

Axis::~Axis()
{

}

void Axis::Update()
{

}

void Axis::ObjectSetting()  
{
	HRESULT hr = S_OK;

	ColorVertex axisvertex[] =
	{
		{DirectX::XMFLOAT3(0.f,0.01f,0.f),DirectX::XMFLOAT4(1.0f,0.0f,0.0f,1.0f)},
		{DirectX::XMFLOAT3(15.f,0.01f,0.f),DirectX::XMFLOAT4(1.0f,0.0f,0.0f,1.0f)},

		{DirectX::XMFLOAT3(0.f,0.f,0.f),DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},
		{DirectX::XMFLOAT3(0.f,15.f,0.f),DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},

		{DirectX::XMFLOAT3(0.f,0.f,0.f),DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
		{DirectX::XMFLOAT3(0.f,0.f,15.f),DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)}
	};

		D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = 6 * sizeof(ColorVertex);
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 버퍼가 파이프라인에 바인딩되는 방법식별
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// 버퍼 초기화는 엔진에서->D3D디바이스를 엔진에서 들고있기 때문에 정보만 넘겨준다.
	// 텍스처 할때 사용한다.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = axisvertex;	// const 무효-> 초기화 데이터에 대한 포인터이다.
	InitData.SysMemPitch = 0;		// 텍스처 한 줄 시작 부분에서 다음줄 까지의 거리(byte)
	InitData.SysMemSlicePitch = 0;	// 한 깊이 수준의 시작부터 다음 수준까지의 거리(byte)

	//D3D엔진에서 디바이스를 여기서 넘겨줘야하나?
	hr = _3DDevice->CreateBuffer
	(
		&bufferDesc,
		&InitData,
		_VertexBuffer.GetAddressOf()
	);


	UINT indices[] =
	{
		0,1,	// x

		2,3,	// y

		4,5		// z
	};

	UINT axiscount = ARRAYSIZE(indices);

	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.ByteWidth = axiscount * sizeof(UINT);
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexInit;
	indexInit.pSysMem = indices;
	indexInit.SysMemPitch = 0;
	indexInit.SysMemSlicePitch = 0;

	hr = _3DDevice->CreateBuffer(
		&indexBufferDesc,
		&indexInit,
		_IndexBuffer.GetAddressOf()
	);

	BuildFX();
	BuildVertexLayout();

}

void Axis::ObjectUpdate(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& projection)
{
	_world = world;
	_view = view;
	_proj = projection;
}


void Axis::Render()
{
	// 입력 배치 객체 셋팅
	_3DDeviceContext->IASetInputLayout(_InputLayout.Get());
	_3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// 인덱스버퍼와 버텍스 버퍼 셋팅
	UINT stride = sizeof(ColorVertex);
	UINT offset = 0;
	_3DDeviceContext->IASetVertexBuffers(0, 1, _VertexBuffer.GetAddressOf(), &stride, &offset);
	// &_axisVertexBuffer와 AddressOf차이가 뭐일까-> &는 초기화를 해버린다.
	_3DDeviceContext->IASetIndexBuffer(_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	///WVP TM등을 셋팅
	DirectX::XMMATRIX worldViewProj = _world * _view * _proj;
	_MatrixVariable->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	//랜더스테이트
	_3DDeviceContext->RSSetState(_RasterState.Get());

	//테크닉
	D3DX11_TECHNIQUE_DESC techDesc;
	_Technique->GetDesc(&techDesc);

	//랜더패스
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		_Technique->GetPassByIndex(p)->Apply(0, _3DDeviceContext.Get());

		_3DDeviceContext->DrawIndexed(6, 0, 0);
	}
}

void Axis::BuildFX()
{
	HRESULT hr = S_OK;
	//이펙트를 쓰는부분은 차차 해보자

	/// 컴파일된 파일도 괜찮고
	/// 컴파일 하는 것도 문제없이 돌아감.

	UINT shaderFlag = D3DCOMPILE_ENABLE_STRICTNESS;	// 쉐이더 컴파일시 엄격한 문법 검사를 수행하도록 하는 컴파일 플래그

#if defined( DEBUG ) || defined( _DEBUG )	// 디버그 모드에서 쉐이더 컴파일시 디버깅에 필요한 정보를 추가
	shaderFlag |= D3D10_SHADER_DEBUG;		// 최적화 과정을 건너뛰도록 설정하는 역할이다.
	shaderFlag |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
	ID3DBlob* compiledShader;
	ID3DBlob* compilationMsgs;


	LPCWSTR shaderFile = L"../fx/color.fx";
	LPCSTR shaderEntryPoint = "main";
	LPCSTR shaderTarget = "fx_5_0";

	hr = D3DCompileFromFile(shaderFile, nullptr, nullptr, shaderEntryPoint, shaderTarget, shaderFlag, 0, &compiledShader, &compilationMsgs);

	D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, _3DDevice.Get(), _Effect.GetAddressOf());

	_Technique = _Effect->GetTechniqueByName("ColorTech");
	_MatrixVariable = _Effect->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void Axis::BuildVertexLayout()
{
	HRESULT hr = S_OK;

	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// Create the input layout
	D3DX11_PASS_DESC passDesc;
	_Technique->GetPassByIndex(0)->GetDesc(&passDesc);

	/// 그냥 숫자 적혀있는게 불편해서 ARRAYSIZE로 바꿈
	/// 아무 의미 없긴 함
	hr = (_3DDevice->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, _InputLayout.GetAddressOf()));

	if (FAILED(hr))
	{
		hr = S_FALSE;
	}
}
