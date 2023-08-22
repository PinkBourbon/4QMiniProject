#include "RenderComponent.h"

RenderComponent::RenderComponent(std::string componentname, act::ParentObject* pObject)
{
	_componentName = componentname;
	_gameObject = pObject;

	renderObject = new aptoCore::Renderable();

	renderObject->drawType = aptoCore::Renderable::DrawType::Solid;
	renderObject->meshType = aptoCore::Renderable::MeshType::StaticMesh;
	renderObject->MeshFilePath = "";
	renderObject->TextureFilePath = "";
	renderObject->NormalMapFilePath = "";
	renderObject->vertexShaderFilePath = "";
	renderObject->pixelShaderFilePath = "";
}

RenderComponent::RenderComponent(std::string componentname, act::ParentObject* pObject
	, aptoCore::Renderable::DrawType drawType, aptoCore::Renderable::MeshType meshType
	, std::string MeshFilePath, std::string TextureFilePath, std::string NormalMapFilePath
	, std::string vertexShaderFilePath, std::string pixelShaderFilePath)
{
	_componentName = componentname;
	_gameObject = pObject;

	renderObject = new aptoCore::Renderable();

	renderObject->drawType = drawType;
	renderObject->meshType = meshType;
	renderObject->MeshFilePath = MeshFilePath;
	renderObject->TextureFilePath = TextureFilePath;
	renderObject->NormalMapFilePath = NormalMapFilePath;
	renderObject->vertexShaderFilePath = vertexShaderFilePath;
	renderObject->pixelShaderFilePath = pixelShaderFilePath;
}

RenderComponent::~RenderComponent()
{
	delete renderObject;
}

void RenderComponent::Awake()
{
}

void RenderComponent::Enable()
{
	RegisterObject(*renderObject);
}

void RenderComponent::Start()
{
}

void RenderComponent::RateUpdate()
{
}

void RenderComponent::Update()
{
}

void RenderComponent::Disable()
{
	DeregisterObject(*renderObject);
}

void RenderComponent::Release()
{
	DeregisterObject(*renderObject);
}
