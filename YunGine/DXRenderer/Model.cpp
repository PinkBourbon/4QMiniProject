#include "Model.h"

Model::Model(std::wstring filePath)
{
	Load(filePath);
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
	
		_3DDeviceContext->DrawIndexed(indexcount, 0, 0);
	}
}

void Model::Load(std::wstring filePath)
{
	FbxLoaderV4* loader = new FbxLoaderV4;
	//loader->Load(filePath, this);
	delete loader;
}

void Model::ObjectSetting()
{
	// Init
	HRESULT hr = S_OK;

	// 만드는 순서
	// shaderResource -> GeometryBuffer -> Effect -> VertexLayout

	// BuildFX();
	// GetTextureFile();
	// BuildFxFromCso();
	// BuildVertexLayout();

}

void Model::BuildFX()
{

}

void Model::GetTextureFile()
{

}

void Model::BuildFxFromCso(ID3D11Device* device, const std::wstring& filename)
{

}

void Model::BuildVertexLayout()
{

}

