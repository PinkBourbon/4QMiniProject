#pragma once
#include <string>

#include "ParentObject.h"

using namespace std;

class TestComponent;
class TestComponent1;
class TestComponent2;

class TestObject_Find :public act::ParentObject
{
public:
	TestObject_Find(string objectName, act::ParentScene* parentScene);
	virtual ~TestObject_Find();
};

