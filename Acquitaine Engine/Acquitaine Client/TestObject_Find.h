#pragma once
#include <string>

#include "ParentObject.h"

class TestComponent;
class TestComponent1;
class TestComponent2;

class TestObject_Find :public act::ParentObject
{
public:
	TestObject_Find(std::string objectName, act::ParentScene* parentScene);
	virtual ~TestObject_Find();
};

