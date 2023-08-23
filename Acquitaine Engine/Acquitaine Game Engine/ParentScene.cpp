#include "ParentScene.h"
#include "GameProcess.h"

namespace act
{

	ParentScene::ParentScene()
		:_gameProcess(GameProcess::s_gameEnginePointer)
	{
		Initialize();
	}

	ParentScene::~ParentScene()
	{
	}

	void ParentScene::Initialize()
	{
		_gameProcess->AddScene(this);
		std::cout << "scene create sucessed" << std::endl;
	}

	void ParentScene::Finalize()
	{
		// 여기서 gameProcess 해제 하지마!!!
		// 게임 오브젝트는 해제해도 되는데 delete 말고 별도 함수 써서 해제 해야함
		// 어차피 스크립트 짤 때 못보게 할거니까 알아서 잘짜..
	}

	void ParentScene::ChangeObjectState(ParentObject* pObject, bool state)
	{
		_gameProcess->ChangeObjectState(pObject, state);
	}

	ParentObject& ParentScene::FindObject(std::string objectname)
	{
		return _gameProcess->FindObject(objectname);
	}

	void ParentScene::DeleteObject(ParentObject* pObject)
	{
		_gameProcess->DeleteObject(pObject);
	}
}