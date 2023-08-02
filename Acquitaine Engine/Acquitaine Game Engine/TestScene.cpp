#include "TestScene.h"
#include "TestObject.h"

TestScene::TestScene(string SceneName)
{
	this->SceneName = SceneName;
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
	AddObject<TestObject>("test0");
	AddObject<TestObject>("test1");
	AddObject<TestObject>("test2");
}
