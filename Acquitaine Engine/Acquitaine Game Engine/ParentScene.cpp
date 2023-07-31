#include "ParentScene.h"

ParentScene::ParentScene()
	:gameProcess(GameProcess::gameEnginePointer)
{
}

ParentScene::~ParentScene()
{
}

void ParentScene::Initialize()
{	
	gameProcess->AddScene(this);
}

void ParentScene::Finalize()
{
	//여기서 gameProcess 해제 하지마!!!
}

void ParentScene::RemoveObject()
{
}

void ParentScene::FindObject()
{
	cout << "있는데?";
}

void ParentScene::ChangeObjectState()
{
}