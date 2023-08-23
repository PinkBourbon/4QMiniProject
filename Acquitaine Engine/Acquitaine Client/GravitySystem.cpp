#include "GravitySystem.h"
#include "SpaceShip.h"
#include "Gravity.h"
#include "TransformComponent.h"

GravitySystem::GravitySystem() :
	gravityMap(),
	ship(nullptr)
{

}

void GravitySystem::Enable()
{
	ship = dynamic_cast<SpaceShip*>(&(_gameObject->FindObject("PlayerShip")));
}

void GravitySystem::Update()
{
	if (ship == nullptr)
	{
		return;
	}

	apto::Vector3f shipPosition = (apto::Vector3f)static_cast<TransformComponent*>(ship->GetComponentPointer<TransformComponent>())->GetPosition();

	for (auto& [name, gravity] : gravityMap)
	{
		//apto::Vector3f gravityPosition = (apto::Vector3f)gravity->_gameObject->GetComponentPointer<TransformComponent>()->GetPosition();
		//float gravityDirection = (gravityPosition - shipPosition).Norm();

		//if (gravityDirection < gravity->_radius)
		//{

		//}
	}
}
