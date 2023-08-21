#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include "d3dx11effect.h"
#include "FbxLoaderV4.h"
#include <vector>

#include <d3dcompiler.h>
#include <d3dcommon.h>

#include "..\\DXTK\Effects.h"

#include "Vertex.h"

class RenderableBase
{
public:
	void SetVertexBuffer(ID3D11Buffer* vertexBuffer);
	void SetIndexBuffer(ID3D11Buffer* indexBuffer);

	// 업데이트와 랜더는 필요
protected:
	virtual void ObjectSetting() abstract;

	virtual void Update() abstract;
	virtual void ObjectUpdate(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& projection) abstract;
	virtual void Render() abstract;

	Microsoft::WRL::ComPtr<ID3D11Device>				_3DDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			_3DDeviceContext;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>		_RasterState;

	Microsoft::WRL::ComPtr<ID3D11Buffer>				_VertexBuffer;		// 정점 버퍼		(정점들의 버퍼?)
	Microsoft::WRL::ComPtr<ID3D11Buffer>				_IndexBuffer;		// 인덱스 버퍼	(정점들의 인덱스?)

	Microsoft::WRL::ComPtr<ID3D11InputLayout>			_InputLayout;		// 엔진에서 이걸 알아야 할까?->여기서 해주면된다.

	Microsoft::WRL::ComPtr<ID3DX11Effect>				_Effect;			// 버텍스 셰이더 픽셀 셰이더를 대체할 무언가
	Microsoft::WRL::ComPtr<ID3DX11EffectTechnique>		_Technique;			// 테크
	Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable>	_MatrixVariable;	// 상수버퍼를 대신할 무언가?

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> _CurrRasterState;		// 레스터스테이트
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> _SolidRasterState;

	DirectX::XMMATRIX _world;	// 월드 변환 행렬 (로컬 -> 월드)
	DirectX::XMMATRIX _view;	// 시야 변환 행렬 (카메라 뷰)
	DirectX::XMMATRIX _proj;	// 투영 변환 행렬 (원근 / 직교)

	ID3D10Blob* _compiledShader = 0;
	ID3D10Blob* _compilationMsgs = 0;

	MyVertex _position;

	// D3D쪽에서 쓰는 버퍼가있으므로 굳이필요하지않음
	//std::vector<Vertex> _vertexVector;
	//std::vector<UINT> _indecies;

};