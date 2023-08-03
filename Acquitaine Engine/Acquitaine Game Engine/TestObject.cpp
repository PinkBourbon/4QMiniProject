#include "TestObject.h"
#include "TestComponent.h"
#include "TestComponent 1.h"
#include "TestComponent 2.h"

TestObject::TestObject(string objectName)
{
	this->objectName = objectName;

	AddComponent<TestComponent>("component0", this);
	AddComponent<TestComponent1>("component1", this);
	AddComponent<TestComponent2>("component2", this);
}

TestObject::~TestObject()
{

}
