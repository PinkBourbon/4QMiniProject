#include "GameScene.h"

#include "SpaceShip.h"
#include "Planet.h"

GameScene::GameScene()
{
	this->_SceneName = "GameScene";

	AddObject<SpaceShip>("spaceShip");
	AddObject<Planet>("plant1");
}

