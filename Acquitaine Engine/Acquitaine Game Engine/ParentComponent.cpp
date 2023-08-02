#include "ParentComponent.h"
#include "IObject.h"

ParentComponent::ParentComponent()
{
	componentIDs++;
	componentID = componentIDs;
}

ParentComponent::~ParentComponent()
{

}

void ParentComponent::SetGameObject(IObject* parentObject)
{
	gameObject = parentObject;
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

void ParentComponent::Disable()
{
}

void ParentComponent::Release()
{
	Finalize();
}
