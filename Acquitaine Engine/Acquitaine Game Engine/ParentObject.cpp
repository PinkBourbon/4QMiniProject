#include "ParentObject.h"
#include "ParentComponent.h"

ParentObject::ParentObject()
	:objectName("Empty_name_space"), objectID(0), componentList(0)
	, includedScene(nullptr), includedSceneID(0)
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
	// dynamic_cast<ParentComponent>(component)->SetGameObject(this);		///RTTI? ÅÛÇÃ¸´? ¹¹¸¦ ½á¾ß ÇÒ±î...
}

void ParentObject::RemoveComponent()
{
}

void ParentObject::Initialize()
{
	for (auto pObject : componentList)
	{
		//pObject->Initialize();
	}
}

void ParentObject::Finalize()
{
	for (auto pObject : componentList)
	{
		//pObject->Finalize();
	}
}

void ParentObject::Awake()
{
	for (auto pObject : componentList)
	{
		//pObject->Awake();
	}
}

void ParentObject::Enable()
{
	for (auto pObject : componentList)
	{
		//pObject->Enable();
	}
}

void ParentObject::Start()
{
	for (auto pObject : componentList)
	{
		//pObject->Start();
	}
}

void ParentObject::InputEvent()
{
}

void ParentObject::FixedUpdate()
{
	for (auto pObject : componentList)
	{
		//pObject->FixedUpdate();
	}
}

void ParentObject::Update()
{
	for (auto pObject : componentList)
	{
		//pObject->Update();
	}
}

void ParentObject::Render()
{
	for (auto pObject : componentList)
	{
		//pObject->Render();
	}
}

void ParentObject::Disable()
{
	for (auto pObject : componentList)
	{
		//pObject->Disable();
	}
}

void ParentObject::Release()
{
	for (auto pObject : componentList)
	{
		//pObject->Release();
	}
	Finalize();
}
