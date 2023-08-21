#include "CameraComponent.h"

CameraComponent::CameraComponent(std::string componentname, act::ParentObject* pObject)
{
	_componentName = componentname;
	_gameObject = pObject;

	_camera = new apto::Camera();
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Awake()
{
}

void CameraComponent::Enable()
{
}

void CameraComponent::Start()
{
}

void CameraComponent::FixedUpdate()
{
}

void CameraComponent::Update()
{
}

void CameraComponent::Disable()
{
}

void CameraComponent::Release()
{
}
