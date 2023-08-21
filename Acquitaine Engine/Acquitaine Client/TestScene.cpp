#include "TestScene.h"
#include "TestObject.h"
#include "TestObject_Find.h"

TestScene::TestScene(std::string SceneName)
{
	this->_SceneName = SceneName;

	AddObject<TestObject>("test0");
	AddObject<TestObject>("test1");
	AddObject<TestObject_Find>("test_find");
}

TestScene::~TestScene()
{

}