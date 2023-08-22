#pragma once
#include "ParentComponent.h"
import apto.graphics.Camera;
import apto.math;

class CameraComponent : public act::ParentComponent
{
public:
	CameraComponent(std::string componentname, act::ParentObject* pObject);
	~CameraComponent();

public:
	virtual void Awake() override;
	virtual void Enable() override;
	virtual void Start() override;

	virtual void RateUpdate() override;
	virtual void Update() override;

	virtual void Disable() override;
	virtual void Release() override;

	/////////// 아래는 카메라를 캡슐링 한거 /////////// 

	void SetPosition(float x, float y, float z);
	void AddPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void AddRotationAxis(const apto::Vector3f& axis, float radian);
	void LookAt(float x, float y, float z);
	void SetPropeties(float viewportWidth, float viewportHeight, float fovDegree = 60.f, float nearZ = 0.1f, float farZ = 10000.f);

	void SetOrthographic();
	void SetPerspective();

	/// 카메라를 내보내는 방법
	apto::Camera* GetCamera();

private:
	apto::Camera* _camera;
};

