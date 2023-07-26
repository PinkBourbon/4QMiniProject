#include "ParentComponent.h"

void ParentComponent::Release()
{
	Finalize();
}

void ParentComponent::SetGameObject(IObject* parentObject)
{
	gameObject = parentObject;
}