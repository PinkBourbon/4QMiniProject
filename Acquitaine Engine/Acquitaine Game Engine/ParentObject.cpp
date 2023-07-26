#include "ParentObject.h"

ParentObject::ParentObject()
	:objectName("Empty_name_space"), objectID(0), componentList(0)
{
	objectIDs++;
	objectID = objectIDs;
}

ParentObject::~ParentObject()
{
}

void ParentObject::AddComponent(IComponent* component)
{
	componentList.push_back(component);
	//component->SetGameObject(this);		///RTTI? ≈€«√∏¥? ππ∏¶ Ω·æﬂ «“±Ó...
}

void ParentObject::RemoveComponent()
{
}

void ParentObject::Initialize()
{
}

void ParentObject::Finalize()
{
}

void ParentObject::Awake()
{
}

void ParentObject::Enable()
{
}

void ParentObject::Start()
{
}

void ParentObject::InputEvent()
{
}

void ParentObject::FixedUpdate()
{
}

void ParentObject::Update()
{
}

void ParentObject::Disable()
{
}

void ParentObject::Release()
{
}
