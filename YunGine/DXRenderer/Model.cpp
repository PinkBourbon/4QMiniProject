#include "Model.h"

Model::Model(std::wstring filePath)
{
	Load(filePath);
}

Model::~Model()
{

}

void Model::Update()
{

}

void Model::ObjectUpdate(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& projection)
{

}

void Model::Render()
{
	// 그리는 부분
}

void Model::Load(std::wstring filePath)
{
	FbxLoaderV4* loader = new FbxLoaderV4;
	loader->Load(filePath);
	delete loader;
}

void Model::ObjectSetting()
{

}

void Model::BuildFX()
{

}

void Model::BuildVertexLayout()
{

}

void Model::BuildFxFromCso(ID3D11Device* device, const std::wstring& filename)
{

}

void Model::GetTextureFile()
{

}
