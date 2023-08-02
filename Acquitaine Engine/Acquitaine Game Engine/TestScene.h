#pragma once
#include "ParentScene.h"

class TestObject;

class TestScene : public ParentScene
{
public:
	TestScene(string SceneName);
	virtual ~TestScene();
	virtual void Initialize() override;
};

