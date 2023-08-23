#include "SceneManager.h"
#include "ParentScene.h"
#include "TestScene.h"

#include "GameScene.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::Initialize()
{
	//여기 안에 scene 들을 넣으시면 됩니다.

// ex) 	ParentScene* scene1 = new TestScene();
// 		scene1->Initialize();
	//act::ParentScene* scene1 = new TestScene("test scene");
	//std::cout << "scene manager create sucessed" << std::endl;
	//scene1->Initialize();

	act::ParentScene* gameScene = new GameScene();
	gameScene->Initialize();
}
