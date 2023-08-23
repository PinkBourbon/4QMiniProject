#include "spaceship.h"
#include "Kinematic.h"
#include "RenderComponent.h"

SpaceShip::SpaceShip() :
	_startDirection(1.0f, 0.0f),
	_startPosition(0.0f, 0.0f),
	_startSpeed(0.0f),
	_collisionRadius(1.0f)
{
	this->objectName = "SpaceShip";

	AddComponent<RenderComponent>("RenderComponent", this);
	AddComponent<Kinematic>("Kinematic", this);
}

