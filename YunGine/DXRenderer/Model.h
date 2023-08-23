#pragma once
#include "RenderableBase.h"

class Model final : public RenderableBase 
{
public:
	Model(
		aptoCore::Renderable& object,
		apto::Transform* transform,
		Microsoft::WRL::ComPtr<ID3D11Device>& pDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pDeviceContext,
		Microsoft::WRL::ComPtr<ID3D11RasterizerState>& pRasterState,
		std::vector<Vertex> Vvector,
		std::vector<unsigned int> Ivector
	);
	~Model();

	virtual void Update() override;
	virtual void ObjectUpdate(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& projection) override;
	virtual void Render() override;

	apto::Transform* transform;
	// D3D쪽에서 쓰는 버퍼가있으므로 굳이필요하지않음
	std::vector<Vertex>* _vertexVector;
	std::vector<unsigned int>* _indecies;

private:
	virtual void ObjectSetting() override;

	void BuildFX();
	void GetTextureFile();
	void BuildFxFromCso(ID3D11Device* device, const std::wstring& filename);
	void BuildVertexLayout();

	unsigned int _fbxVertexCount;
	unsigned int _fbxIndexCount;

	Microsoft::WRL::ComPtr<ID3D11InputLayout>			_textureModelInputLayout;
	Microsoft::WRL::ComPtr<ID3DX11Effect>				_textureModelEffect;			// 버텍스 셰이더 픽셀 셰이더를 대체할 무언가
	Microsoft::WRL::ComPtr<ID3DX11EffectTechnique>		_textureModelTechnique;		// 테크
	Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable> _textureModelMatrixVariable;	// 상수버퍼를 대신할 무언가?
	
	/// 텍스처를 위한 멤버변수
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	_diffuseMapSRV;
	Microsoft::WRL::ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseMap;
	Microsoft::WRL::ComPtr <ID3DX11EffectMatrixVariable> _gworldMatrixVariable;

	int _indexcount;

};

