#pragma once
#include "RenderableBase.h"
#include <string>

class Model : public RenderableBase 
{
public:
	Model(std::wstring filePath);
	~Model();

	virtual void Update() override;
	virtual void ObjectUpdate(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& projection) override;
	virtual void Render() override;

private:
	void Load(std::wstring filePath);

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

	int indexcount;
};

