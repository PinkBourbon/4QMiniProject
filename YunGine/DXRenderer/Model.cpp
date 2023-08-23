#include "Model.h"
#include "TextureLoader.h"
#include "Utility.h"

#include <fstream>

Model::Model(
	aptoCore::Renderable& object,
	apto::Transform* transform,
	Microsoft::WRL::ComPtr<ID3D11Device>& pDevice,
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pDeviceContext,
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>& pRasterState,
	std::vector<Vertex> Vvector,
	std::vector<unsigned int> Ivector) : 
	transform(transform),
	_vertexVector(&Vvector),
	_indecies(&Ivector)
{
	pDevice.CopyTo(_3DDevice.GetAddressOf());
	pDeviceContext.CopyTo(_3DDeviceContext.GetAddressOf());
	pRasterState.CopyTo(_RasterState.GetAddressOf());

	this->renderable = object;
	ObjectSetting();
}

Model::~Model()
{
	
}

void Model::Update()
{

}

void Model::ObjectUpdate(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& projection)
{
	_world = world;
	_view = view;
	_proj = projection;
}

void Model::Render()
{
	// 그리는 부분
		// 입력 배치 객체 셋팅
	_3DDeviceContext->IASetInputLayout(_InputLayout.Get());
	_3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 인덱스버퍼와 버텍스 버퍼 셋팅
	UINT stride = sizeof(TexVertex);
	UINT offset = 0;

	_3DDeviceContext->IASetVertexBuffers(0, 1, _VertexBuffer.GetAddressOf(), &stride, &offset);
	// &_cubVertexBuffer와 AddressOf차이가 뭐일까-> &는 초기화를 해버린다.
	_3DDeviceContext->IASetIndexBuffer(_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	///WVP TM등을 셋팅
	_world = this->transform->GetMatrix4f();	// 무슨 차이지?
	DirectX::XMMATRIX worldViewProj = _world * _view * _proj;

	_textureModelMatrixVariable->SetMatrix(reinterpret_cast<float*>(&worldViewProj));
	_gworldMatrixVariable->SetMatrix(reinterpret_cast<float*>(&_world));

	//_diffuseMap->SetResource(_diffuseMapSRV.Get());

	//랜더스테이트
	_3DDeviceContext->RSSetState(_RasterState.Get());

	//테크닉
	D3DX11_TECHNIQUE_DESC techDesc;
	_textureModelTechnique->GetDesc(&techDesc);

	//랜더패스
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		_textureModelTechnique->GetPassByIndex(p)->Apply(0, _3DDeviceContext.Get());

		_3DDeviceContext->DrawIndexed(_indexcount, 0, 0);
	}
}

void Model::ObjectSetting()
{
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(Vertex) * _vertexVector->size();//60 * size(*_vertexVector);
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 버퍼가 파이프라인에 바인딩되는 방법식별
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	// 버퍼 초기화는 엔진에서->D3D디바이스를 엔진에서 들고있기 때문에 정보만 넘겨준다.
	// 텍스처 할때 사용한다.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &((*_vertexVector)[0]);
	//InitData.pSysMem = &(_vertexVector[0]);	// const 무효-> 초기화 데이터에 대한 포인터이다.
	InitData.SysMemPitch = 0;		// 텍스처 한 줄 시작 부분에서 다음줄 까지의 거리(byte)
	InitData.SysMemSlicePitch = 0;	// 한 깊이 수준의 시작부터 다음 수준까지의 거리(byte)

	hr = _3DDevice->CreateBuffer
	(
		&bufferDesc,
		&InitData,
		&_VertexBuffer
	);

	if (FAILED(hr))
	{
		hr = S_FALSE;
	}

	_indexcount = size(*_indecies);

	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	//indexBufferDesc.ByteWidth = modelindexcount * sizeof(UINT);
	indexBufferDesc.ByteWidth = sizeof(_indecies); // 차이가 없다
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexInit;
	indexInit.pSysMem = &(_indecies[0]);
	indexInit.SysMemPitch = 0;
	indexInit.SysMemSlicePitch = 0;

	hr = _3DDevice->CreateBuffer(
		&indexBufferDesc,
		&indexInit,
		&_IndexBuffer
	);

	if (FAILED(hr))
	{
		hr = S_FALSE;
	}

	GetTextureFile();
	BuildFxFromCso(_3DDevice.Get(), L"../fx/Basic.cso");
	BuildVertexLayout();
}

void Model::BuildFX()
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

	LPCWSTR shaderFile = L"../fx/Basic.fx";
	LPCSTR shaderEntryPoint = "VS";
	LPCSTR shaderTarget = "fx_5_0";

	hr = D3DCompileFromFile(shaderFile, nullptr, nullptr, shaderEntryPoint, shaderTarget, shaderFlag, 0, &compiledShader, &compilationMsgs);

	//D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, _3DDevice.Get(), _textureboxEffect.GetAddressOf());

	_Technique = _textureModelEffect->GetTechniqueByName("TextureTech");
	_textureModelMatrixVariable = _textureModelEffect->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void Model::GetTextureFile()
{
	HRESULT hr = S_OK;
	std::wstring wstrFilePath;
	strtowstr(renderable.TextureFilePath, &wstrFilePath);

	Microsoft::WRL::ComPtr<ID3D11Resource> texResource = nullptr;	// Release를 제대로 할 수 있을까?
	DirectX::CreateDDSTextureFromFile(
		_3DDevice.Get(),
		wstrFilePath.c_str(),
		&texResource,
		&_diffuseMapSRV);

	if (FAILED(hr))
	{
		hr = S_FALSE;
	}
}

void Model::BuildFxFromCso(ID3D11Device* device, const std::wstring& filename)
{
	std::ifstream fin(filename, std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	HRESULT hr = D3DX11CreateEffectFromMemory(&compiledShader[0], size,
		0, device, &_textureModelEffect);

	_textureModelTechnique = _textureModelEffect->GetTechniqueByName("TextureTech");
	_textureModelMatrixVariable = _textureModelEffect->GetVariableByName("gWorldViewProj")->AsMatrix();	// 행렬로 쓸꺼야
	_gworldMatrixVariable = _textureModelEffect->GetVariableByName("gWorld")->AsMatrix();	// 행렬로 쓸꺼야

	_diffuseMap = _textureModelEffect->GetVariableByName("gDiffuseMap")->AsShaderResource();

	BOOL res = _textureModelEffect->IsValid();	// 메모리가 쓰레기값이 아닌지를 확인하는 함수
	res = _textureModelTechnique->IsValid();
	res = _textureModelMatrixVariable->IsValid();
	res = _gworldMatrixVariable->IsValid();
	res = _diffuseMap->IsValid();

	if (FAILED(hr))
	{
		hr = S_FALSE;
	}
}

void Model::BuildVertexLayout()
{
	HRESULT hr = S_OK;

	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"UV",    0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"BINORMAL",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TANGENT",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 46, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	D3DX11_PASS_DESC passDesc;
	_textureModelTechnique->GetPassByIndex(0)->GetDesc(&passDesc);

	hr = (_3DDevice->CreateInputLayout(
		vertexDesc,
		ARRAYSIZE(vertexDesc),
		passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize,
		_InputLayout.GetAddressOf()
	));

	if (FAILED(hr))
	{
		hr = S_FALSE;
	}
}

