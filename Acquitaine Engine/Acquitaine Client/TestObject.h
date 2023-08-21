#pragma once
#include <string>

#include "ParentObject.h"

using namespace std;

class TestComponent;
class TestComponent1;
class TestComponent_Find;
class TransformComponent;

class TestObject :public act::ParentObject
{
public:
	TestObject(string objectName, act::ParentScene* parentScene);
	virtual ~TestObject();
};

