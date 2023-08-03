#include "TestScene.h"
#include "TestObject.h"

TestScene::TestScene(string SceneName)
{
	this->_SceneName = SceneName;

	AddObject<TestObject>("test0");
	AddObject<TestObject>("test1");
	AddObject<TestObject>("test2");
}

TestScene::~TestScene()
{
}