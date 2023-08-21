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
};

