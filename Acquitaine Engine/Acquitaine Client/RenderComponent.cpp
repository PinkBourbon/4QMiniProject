#include "RenderComponent.h"

RenderComponent::RenderComponent(std::string componentname, act::ParentObject* pObject)
{
	_componentName = componentname;
	_gameObject = pObject;

	_renderObject = new aptoCore::Renderable();

	_renderObject->drawType = aptoCore::Renderable::DrawType::Solid;
	_renderObject->meshType = aptoCore::Renderable::MeshType::StaticMesh;
	_renderObject->MeshFilePath = "";
	_renderObject->TextureFilePath = "";
	_renderObject->NormalMapFilePath = "";
	_renderObject->vertexShaderFilePath = "";
	_renderObject->pixelShaderFilePath = "";
}

RenderComponent::~RenderComponent()
{
	delete _renderObject;
}

void RenderComponent::Awake()
{
	//RegisterObject(*_renderObject);
}

void RenderComponent::Enable()
{
	//RegisterObject(*_renderObject);
}
 
void RenderComponent::Start()
{
	//RegisterObject(*_renderObject);
}

void RenderComponent::RateUpdate()
{

}

void RenderComponent::Update()
{
}

void RenderComponent::Disable()
{
	DeregisterObject(*_renderObject);
}

void RenderComponent::Release()
{
	DeregisterObject(*_renderObject);
}

void RenderComponent::SetRenderable(aptoCore::Renderable::DrawType drawType, aptoCore::Renderable::MeshType meshType
									, std::string MeshFilePath, std::string TextureFilePath, std::string NormalMapFilePath
									, std::string vertexShaderFilePath, std::string pixelShaderFilePath)
{
	_renderObject->drawType = drawType;
	_renderObject->meshType = meshType;
	_renderObject->MeshFilePath = MeshFilePath;
	_renderObject->TextureFilePath = TextureFilePath;
	_renderObject->NormalMapFilePath = NormalMapFilePath;
	_renderObject->vertexShaderFilePath = vertexShaderFilePath;
	_renderObject->pixelShaderFilePath = pixelShaderFilePath;
}

aptoCore::Renderable& RenderComponent::GetRenderable()
{
	return *_renderObject;
}
