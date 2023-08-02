#pragma once
#include <string>

#include "ParentObject.h"
using namespace std;

class TestObject :public ParentObject
{
public:
	TestObject(string objectName);
	~TestObject();
};

