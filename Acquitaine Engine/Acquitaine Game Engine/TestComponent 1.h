#pragma once
#include <iostream>

#include "ParentComponent.h"  

class ParentObject;

class TestComponent1 : public ParentComponent
{
public:
	TestComponent1(string name, ParentObject* pObject);
	virtual ~TestComponent1();

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void InputEvent() override;
	virtual void Render() override;
	virtual void Phsics()override;
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//

	virtual void Awake() override;
	virtual void Enable() override;
	virtual void Start() override;

	virtual void FixedUpdate() override;
	virtual void Update() override;

	virtual void Disable() override;
	virtual void Release() override;
};

