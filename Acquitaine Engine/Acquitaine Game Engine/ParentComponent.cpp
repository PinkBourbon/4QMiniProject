#include "ParentComponent.h"
#include "ParentObject.h";

namespace act
{

	ParentComponent::ParentComponent()
		: _gameObject(nullptr), _isEnabled(true), _componentName("name is empty.")
	{

	}

	ParentComponent::~ParentComponent()
	{

	}

	void ParentComponent::SetGameObject(ParentObject* parentObject)
	{
		_gameObject = parentObject;
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

	void ParentComponent::FixedUpdate()
	{
	}

	void ParentComponent::Update()
	{
	}

	void ParentComponent::Phsics()
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