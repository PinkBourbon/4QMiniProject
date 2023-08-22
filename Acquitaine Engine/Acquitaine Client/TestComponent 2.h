#pragma once
#include <iostream>

#include "ParentComponent.h"  

class ParentObject;

class TestComponent2 : public act::ParentComponent
{
public:
	TestComponent2(std::string name, act::ParentObject* pObject);
	virtual ~TestComponent2();

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void InputEvent() override;
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//

	virtual void Awake() override;
	virtual void Enable() override;
	virtual void Start() override;

	virtual void RateUpdate() override;
	virtual void Update() override;

	virtual void Disable() override;
	virtual void Release() override;
};

