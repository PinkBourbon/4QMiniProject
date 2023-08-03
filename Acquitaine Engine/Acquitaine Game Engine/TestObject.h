#pragma once
#include <string>

#include "ParentObject.h"

using namespace std;

class TestComponent;
class TestComponent1;
class TestComponent2;

class TestObject :public ParentObject
{
public:
	TestObject(string objectName);
	virtual ~TestObject();
};

