#include "RenderComponent.h"
#include "importGraphics.h"

RenderComponent::RenderComponent(std::string componentname, act::ParentObject* pObject)
{
	renderObject = new Renderable();

	renderObject->drawType = Renderable::DrawType::Solid;
	renderObject->meshType = Renderable::MeshType::StaticMesh;
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
