#include "ParentObject.h"
#include "ParentComponent.h"
#include "ParentScene.h"

namespace act
{

	int ParentObject::_objectIDs;

	ParentObject::ParentObject()
		:objectName("Empty_name_space"), _objectID(0), _componentList(0)
		, _includedScene(nullptr), _includedSceneID(0), isEnabled(true)
	{
		_objectIDs = 0;

		_objectIDs++;
		_objectID = _objectIDs;
	}

	ParentObject::~ParentObject()
	{
	}

	std::vector<ParentComponent*>& ParentObject::GetComponentlist()
{
		return _componentList;
	}

	void ParentObject::RemoveComponent()
	{
	}

	void ParentObject::Initialize()
	{
		for (auto pComponent : _componentList)
		{
			pComponent->Initialize();
		}
	}

	void ParentObject::Finalize()
	{
		for (auto pComponent : _componentList)
		{
			pComponent->Finalize();
			delete pComponent;
		}
		_componentList.clear();
	}

	ParentObject& ParentObject::FindObject(std::string objectname)
	{
		return _includedScene->FindObject(objectname);
	}

	void ParentObject::Awake()
	{
		for (auto pComponent : _componentList)
		{
			pComponent->Awake();
		}
	}

	void ParentObject::Delete()
	{
		_includedScene->DeleteObject(this);
	}

	void ParentObject::Enable()
	{
		if (!isEnabled)
		{
			for (auto pComponent : _componentList)
			{
				pComponent->Enable();
				isEnabled = true;
			}
		}
	}

	void ParentObject::Start()
	{
		for (auto pComponent : _componentList)
		{
			pComponent->Start();
		}
	}

	void ParentObject::InputEvent()
	{
	}

	void ParentObject::RateUpdate()
	{
		for (auto pComponent : _componentList)
		{
			pComponent->RateUpdate();
		}
	}

	void ParentObject::Update()
	{
		for (auto pComponent : _componentList)
		{
			pComponent->Update();
		}
	}

	void ParentObject::SetActive(bool state)
	{
		_includedScene->ChangeObjectState(this, state);
	}

	void ParentObject::Disable()
	{
		if (isEnabled)
		{
			for (auto pComponent : _componentList)
			{
				pComponent->Disable();
			}
			isEnabled = false;
		}
	}

	void ParentObject::Release()
	{
		for (auto pComponent : _componentList)
		{
			pComponent->Release();
		}
		Finalize();
	}

	float ParentObject::GetDeltaTime()
	{
		return _includedScene->GetDeltaTime();
	}

}