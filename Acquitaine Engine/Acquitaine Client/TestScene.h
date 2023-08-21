#pragma once
#include "ParentScene.h"

class TestObject;

class TestScene : public act::ParentScene
{
public:
	TestScene(std::string SceneName);
	virtual ~TestScene();
};