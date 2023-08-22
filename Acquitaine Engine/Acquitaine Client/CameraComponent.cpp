#include "CameraComponent.h"

CameraComponent::CameraComponent(std::string componentname, act::ParentObject* pObject)
{
	_componentName = componentname;
	_gameObject = pObject;

	_camera = new apto::Camera();
}

CameraComponent::~CameraComponent()
{
	delete _camera;
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

void CameraComponent::RateUpdate()
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

/////////// 아래는 카메라를 캡슐링 한거 /////////// 

void CameraComponent::SetPosition(float x, float y, float z)
{
	_camera->SetPosition(x, y, z);
}

void CameraComponent::AddPosition(float x, float y, float z)
{
	_camera->AddPosition(x, y, z);
}

void CameraComponent::SetRotation(float x, float y, float z)
{
	_camera->SetRotation(x, y, z);
}

void CameraComponent::AddRotationAxis(const apto::Vector3f& axis, float radian)
{
	_camera->AddRotationAxis(axis, radian);
}

void CameraComponent::LookAt(float x, float y, float z)
{
	_camera->LookAt(x, y, z);
}

void CameraComponent::SetPropeties(float viewportWidth, float viewportHeight, float fovDegree, float nearZ, float farZ)
{
	_camera->SetPropeties(viewportWidth, viewportHeight, fovDegree, nearZ, farZ);
}

void CameraComponent::SetOrthographic()
{
	_camera->SetOrthographic();
}

void CameraComponent::SetPerspective()
{
	_camera->SetPerspective();
}

apto::Camera* CameraComponent::GetCamera()
{
	return _camera;
}
