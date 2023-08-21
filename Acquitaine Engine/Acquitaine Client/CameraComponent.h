#pragma once
#include "ParentComponent.h"
import apto.graphics.Camera;

class CameraComponent : public act::ParentComponent
{
public:
	CameraComponent();
	~CameraComponent();

public:
	virtual void Awake() override;
	virtual void Enable() override;
	virtual void Start() override;

	virtual void FixedUpdate() override;
	virtual void Update() override;

	virtual void Disable() override;
	virtual void Release() override;

	/////////// 아래는 카메라를 캡슐링 한거 /////////// 


};

