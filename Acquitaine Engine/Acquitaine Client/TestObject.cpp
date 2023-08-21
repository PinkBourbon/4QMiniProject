#include "TestObject.h"
#include "TestComponent.h"
#include "TestComponent 1.h"
#include "TestComponent 2.h"
#include "TransformComponent.h"

TestObject::TestObject(std::string objectName, act::ParentScene* parentScene)
{
	this->objectName = objectName;
	this->_includedScene = parentScene;

	AddComponent<TestComponent>("component0", this);
	AddComponent<TestComponent1>("component1", this);
	AddComponent<TransformComponent>("", this);
}

TestObject::~TestObject()
{

}
