#include "Kinematic.h"
#include "TransformComponent.h"
#include "ParentObject.h"


Kinematic::Kinematic(std::string name, act::ParentObject* pObject) :
	velocity(0.0f, 0.0f)
{
	_componentName = name;
	_gameObject = pObject;
}

void Kinematic::Update()
{
	static_cast<TransformComponent*>(_gameObject->GetComponentPointer<TransformComponent>())->AddPosition(velocity.x, 0.0f, velocity.y);
}
