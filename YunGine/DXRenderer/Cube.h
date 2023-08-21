#pragma once
#include <iostream>
#include "RenderableBase.h"

import apto.Transform;

class Cube final : public RenderableBase
{
public:
	Cube(
		Microsoft::WRL::ComPtr<ID3D11Device>& pDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pDeviceContext,
		Microsoft::WRL::ComPtr<ID3D11RasterizerState>& pRasterState,
		std::string& name
	);
	~Cube();

	virtual void Update() override;
	virtual void ObjectUpdate(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& projection) override;
	virtual void Render() override;

	// 이름
	std::string name;
	apto::Transform* transform;

private:
	virtual void ObjectSetting() override;

	void BuildFX();
	void BuildVertexLayout();

	void BuildFxFromCso(ID3D11Device* device, const std::wstring& filename);
	void GetTextureFile();

	Microsoft::WRL::ComPtr<ID3D11InputLayout>			_textureboxInputLayout;

	Microsoft::WRL::ComPtr<ID3DX11Effect>				_textureboxEffect;			// 버텍스 셰이더 픽셀 셰이더를 대체할 무언가
	Microsoft::WRL::ComPtr<ID3DX11EffectTechnique>		_textureboxTechnique;		// 테크
	Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable> _textureboxMatrixVariable;	// 상수버퍼를 대신할 무언가?

	int indexcount = 0;

	/// 텍스처를 위한 멤버변수
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	_diffuseMapSRV;
	Microsoft::WRL::ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseMap;
	Microsoft::WRL::ComPtr <ID3DX11EffectMatrixVariable> _gworldMatrixVariable;

};

