#pragma once
#include <iostream>

#include "ParentComponent.h"  

class ParentObject;
class ParentComponent2;

class TestComponent1 : public act::ParentComponent
{
public:
	TestComponent1(std::string name, act::ParentObject* pObject);
	virtual ~TestComponent1();

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//

	virtual void Awake() override;
	virtual void Enable() override;
	virtual void Start() override;

	virtual void RateUpdate() override;
	virtual void Update() override;

	virtual void Disable() override;
	virtual void Release() override;
};

