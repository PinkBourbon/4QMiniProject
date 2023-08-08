#include "ParentComponent.h"
#include "ParentObject.h";

ParentComponent::ParentComponent()
	: _gameObject(nullptr), _isEnabled(true)
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

void ParentComponent::Render()
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
