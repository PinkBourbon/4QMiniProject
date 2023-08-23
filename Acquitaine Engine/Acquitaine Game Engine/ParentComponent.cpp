#include "ParentComponent.h"
#include "ParentObject.h";

namespace act
{

	ParentComponent::ParentComponent()
		: _gameObject(nullptr), _isEnabled(true), _componentName("name is empty.")
	{

	}

	ParentComponent::ParentComponent(std::string componentname, act::ParentObject* pObject)
		: _gameObject(pObject), _isEnabled(true), _componentName(componentname)
	{

	}

	ParentComponent::~ParentComponent()
	{

	}

	void ParentComponent::SetGameObject(ParentObject* parentObject)
	{
		_gameObject = parentObject;
	}

	act::ParentObject& ParentComponent::GetGameObject()
{
		return *_gameObject;
	}

	std::string ParentComponent::GetComonentName()
	{
		return _componentName;
	}

	void ParentComponent::Initialize()
	{
	}

	void ParentComponent::Finalize()
	{
	}

	void ParentComponent::Awake()
	{
	}

	void ParentComponent::Enable()
	{
	}

	void ParentComponent::Start()
	{
	}

	void ParentComponent::InputEvent()
	{
	}

	void ParentComponent::RateUpdate()
	{
	}

	void ParentComponent::Update()
	{
	}

	void ParentComponent::Disable()
	{
	}

	void ParentComponent::Release()
	{
		Finalize();
	}

}