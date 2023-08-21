#include "TransformComponent.h"

TransformComponent::TransformComponent(std::string componentname, act::ParentObject* pObject)
{
	_gameObject = pObject;
	_componentName = "Transform";
	_transform = new Transform();
}

TransformComponent::~TransformComponent()
{
	delete _transform;
}

void TransformComponent::Awake()
{

}

void TransformComponent::Enable()
{
}

void TransformComponent::Start()
{
}

void TransformComponent::FixedUpdate()
{
}

void TransformComponent::Update()
{
}

void TransformComponent::Disable()
{
}

void TransformComponent::Release()
{

}

/// 트렌스폼 객체를 받아야 할때 사용 할 수 있는 함수. 포인터를 반환.
Transform* TransformComponent::GetTransform()
{
	return _transform;
}

///////////////////////////////////////////////////////////////////////////////////
//캡슐라이징 해둔거.

void TransformComponent::SetPosition(float x, float y, float z)
{
	_transform->SetPosition(x, y, z);
}

void TransformComponent::SetRotation(float degreeX, float degreeY, float degreeZ)
{
	_transform->SetRotation(degreeX, degreeY, degreeZ);
}

void TransformComponent::SetScale(float x, float y, float z)
{
	_transform->SetScale(x, y, z);
}

void TransformComponent::AddPosition(float x, float y, float z)
{
	_transform->AddPosition(x, y, z);
}

void TransformComponent::AddRotation(const float x, const float y, const float z, float radian)
{
	apto::Vector3f temp = { x,y,z };
	_transform->AddRotation(temp, radian);
}

void TransformComponent::AddScale(float x, float y, float z)
{
	_transform->AddScale(x, y, z);
}

void TransformComponent::LookAt(const float x, const float y, const float z, const float w)
{
	apto::Vector4f temp = { x,y,z,w };
	_transform->LookAt(temp);
}

apto::Vector4f TransformComponent::GetPosition()
{
	return _transform->GetPosition();
}

apto::Quaternion TransformComponent::GetRotation()
{
	return _transform->GetRotation();
}

apto::Vector4f TransformComponent::GetScale()
{
	return _transform->GetScale();
}
