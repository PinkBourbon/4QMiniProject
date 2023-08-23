#include "GameScene.h"

#include "SpaceShip.h"

GameScene::GameScene()
{
	this->_SceneName = "GameScene";

	AddObject<SpaceShip>("spaceShip");
}

