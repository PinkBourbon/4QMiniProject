#include "spaceship.h"
#include "Kinematic.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

SpaceShip::SpaceShip(std::string objectName, act::ParentScene* parentScene) :
	_startDirection(1.0f, 0.0f),
	_startPosition(0.0f, 0.0f),
	_startSpeed(0.0f),
	_collisionRadius(1.0f)
{
	this->objectName = objectName;
	this->_includedScene = parentScene;

	AddComponent<TransformComponent>("Transform", this);
	AddComponent<RenderComponent>("spaceShip", this);

	RenderComponent* renderComponent = GetComponentPointer<RenderComponent>();
	renderComponent->SetRenderable(
		aptoCore::Renderable::DrawType::Solid,
		aptoCore::Renderable::MeshType::StaticMesh,
		"spaceship.fbx",
		"",
		"",
		"",
		"");

	AddComponent<Kinematic>("Kinematic", this);
}

