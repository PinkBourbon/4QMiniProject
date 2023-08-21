#include "TestObject_Find.h"
#include "TestComponent.h"
#include "TestComponent 1.h"
#include "TestComponent 2.h"

TestObject_Find::TestObject_Find(std::string objectName, act::ParentScene* parentScene)
{
	this->objectName = objectName;
	this->_includedScene = parentScene;

	AddComponent<TestComponent2>("component_Find", this);
}

TestObject_Find::~TestObject_Find()
{

}
