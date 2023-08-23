#include "Planet.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

Planet::Planet(std::string name, act::ParentScene* parentScene) :
	_radius(1.0f)
{
	this->objectName = name;
	this->_includedScene = parentScene;

	AddComponent<TransformComponent>("Transform", this);

	AddComponent<RenderComponent>("spaceShip", this);

	RenderComponent* renderComponent = static_cast<RenderComponent*>(GetComponentPointer<RenderComponent>());
	
	renderComponent->SetRenderable(
		aptoCore::Renderable::DrawType::Solid,
		aptoCore::Renderable::MeshType::StaticMesh,
		"Cube",
		"",
		"",
		"",
		"");
}
