#pragma once
#include "ParentComponent.h"

import apto.Transform;

class TransformComponent:public act::ParentComponent
{
public:
	TransformComponent(std::string componentname, act::ParentObject* pObject);
	virtual ~TransformComponent();

	virtual void Awake() override;
	virtual void Enable() override;
	virtual void Start() override;

	virtual void RateUpdate() override;
	virtual void Update() override;

	virtual void Disable() override;
	virtual void Release() override;

	apto::Transform* GetTransform();

	///	이 아래는 apto.transform을 캡슐링 해놓은 함수들
	void SetPosition(float x, float y, float z);
	void SetRotation(float degreeX, float degreeY, float degreeZ);
	void SetScale(float x, float y, float z);
	void AddPosition(float x, float y, float z);
	void AddRotation(const float x, const float y, const float z, float radian);
	void AddScale(float x, float y, float z);

	void LookAt(const float x, const float y, const float z, const float w);
	apto::Vector4f GetPosition();
	apto::Quaternion GetRotation();   
	apto::Vector4f GetScale(); 

private:
	apto::Transform* _transform;
};

