#pragma once
#include <string>

#include "ParentObject.h"

using namespace std;

class TestComponent;
class TestComponent1;
class TestComponent_Find;

class TestObject :public ParentObject
{
public:
	TestObject(string objectName, ParentScene* parentScene);
	virtual ~TestObject();
};

