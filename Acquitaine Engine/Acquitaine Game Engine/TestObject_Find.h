#pragma once
#include <string>

#include "ParentObject.h"

using namespace std;

class TestComponent;
class TestComponent1;
class TestComponent2;

class TestObject_Find :public ParentObject
{
public:
	TestObject_Find(string objectName, ParentScene* parentScene);
	virtual ~TestObject_Find();
};

