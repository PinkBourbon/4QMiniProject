#include "RenderComponent.h"

RenderComponent::RenderComponent(std::string componentname, act::ParentObject* pObject)
{
	renderObject = new aptoCore::Renderable();

	renderObject->drawType = aptoCore::Renderable::DrawType::Solid;
	renderObject->meshType = aptoCore::Renderable::MeshType::StaticMesh;
	renderObject->MeshFilePath = "";
	renderObject->TextureFilePath = "";
	renderObject->NormalMapFilePath = "";
	renderObject->vertexShaderFilePath = "";
	renderObject->pixelShaderFilePath = "";
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

void RenderComponent::FixedUpdate()
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
