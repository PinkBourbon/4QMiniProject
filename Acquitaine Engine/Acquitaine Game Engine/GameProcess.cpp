#include "GameProcess.h"
#include "TestScene.h"
#include "SceneManager.h"
#include "ParentObject.h"

import aptoCore.Graphics;

GameProcess::GameProcess()
{
}

GameProcess::~GameProcess()
{
}

void GameProcess::Initialize()
{
	s_gameEnginePointer = this;

	_sceneManager = new SceneManager();
	_sceneManager->Initialize();

	bool ret = aptoCore::Graphics::Initialize();

	cout << "Engine Initialized sucess" << endl;
}

void GameProcess::Finalize()
{
	aptoCore::Graphics::Finalize();
}

void GameProcess::RunningGameProcess(double deltaTime)
{
	cout << endl<< "Engine is working" << endl<< endl;

	float fixedupdateTimeRate = 0;

	/// 스크립팅 할때 보이지 않는 부분ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	ObjectStateChange();

	/// 스크립팅 할때 보이는 부분ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	// 초기화,추가, 시작
	Awake();
	Enable();
	Start();

	// 인풋 입력, 물리연산, 업데이트
	InputEvent(); /// 얘는 스크립팅 할때 보이지 않게 할것.
	while (fixedupdateTimeRate > FixedUpdate());	//물리연산이 들어간 부분. 실행시간이 fixedupdatetime보다 작다면 픽스드 업데이트를 반복 실행한다.
	Update();

	Render();	/// 얘는 스크립팅 할때 보이지 않게 할것.

	// 비활성화, 사용 종료
	Disable();
	Release();

	/// 스크립팅 할때 보이지 않는 부분ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	InitializeObjects();

	Sleep(1000);
}

void GameProcess::AddScene(ParentScene* pscene)
{
	_SceneList.push_back(pscene);
}

void GameProcess::InitializeObjects()
{
	for (auto pObject : _waitingObjectList)
	{
		pObject->Initialize();
		PutStateChangeBuffer(eObjectState::WAITING, eObjectState::START, pObject);
	}
	_waitingObjectList.clear();
}

void GameProcess::Awake()
{
	for (auto pObject : _awakeObjectList)
	{
		pObject->Awake();
		PutStateChangeBuffer( eObjectState::AWAKE, eObjectState::UPDATE, pObject);
	}
}

void GameProcess::Enable()
{
	for (auto pObject : _enableObjectList)
	{
		pObject->Enable();
		PutStateChangeBuffer(eObjectState::ENABLE, eObjectState::UPDATE, pObject);
	}
}

void GameProcess::Start()
{
	for (auto pObject : _startObjectList)
	{
		pObject->Start();
		PutStateChangeBuffer(eObjectState::START, eObjectState::UPDATE, pObject);
	}
}

void GameProcess::InputEvent()
{
	for (auto pObject : _objectList)
	{
		pObject->InputEvent();
	}
}

float GameProcess::FixedUpdate()
{
	///물리연산이 실행되는 부분이고, 실행 시간을 초단위로 반환하도록 구성
	for (auto pObject : _fixedUpdateObjectList)
	{
		pObject->FixedUpdate();
		pObject->Phsics();
	}

	return 0.0;
}

void GameProcess::Update()
{
	for (auto pObject : _updateObjectList)
	{
		pObject->Update();
	}
}

void GameProcess::Render()
{
	for (auto pObject : _objectList)
	{
		pObject->Render();
	}
}

void GameProcess::Disable()
{
	for (auto pObject : _disableObjectList)
	{
		pObject->Disable();
	}
}

void GameProcess::Release()
{
	for (auto pObject : _releaseObjectList)
	{
		pObject->Release();
	}
}

void GameProcess::ObjectStateChange()
{
	for (auto buff : _stateChangeBuffer)
	{
		switch (get<1>(buff))
		{
			case eObjectState::AWAKE:
			{
				_awakeObjectList.insert(get<2>(buff));
			}break;
			case eObjectState::ENABLE:
			{
				_enableObjectList.insert(get<2>(buff));
			}break;
			case eObjectState::START:
			{
				_startObjectList.insert(get<2>(buff));
			}break;
			case eObjectState::UPDATE:
			{
				_updateObjectList.insert(get<2>(buff));
			}break;
			case eObjectState::DISABLE:
			{
				_disableObjectList.insert(get<2>(buff));
			}break;
			case eObjectState::RELEASE:
			{
				_releaseObjectList.insert(get<2>(buff));
			}break;
			default:
			{

			}break;
		}
		switch (get<0>(buff))
		{
			case eObjectState::AWAKE:
			{
				_awakeObjectList.erase(
					_awakeObjectList.find(get<2>(buff)));
			}break;
			case eObjectState::ENABLE:
			{
				_enableObjectList.erase(
					_enableObjectList.find(get<2>(buff)));
			}break;
			case eObjectState::START:
			{
				_startObjectList.erase(
					_startObjectList.find(get<2>(buff)));
			}break;
			case eObjectState::UPDATE:
			{
				_updateObjectList.erase(
					_updateObjectList.find(get<2>(buff)));
			}break;
			case eObjectState::DISABLE:
			{
				_disableObjectList.erase(
					_disableObjectList.find(get<2>(buff)));
			}break;
			case eObjectState::RELEASE:
			{
				_releaseObjectList.erase(
					_releaseObjectList.find(get<2>(buff)));
			}break;
			default:
			{

			}break;
		}
	}

	_stateChangeBuffer.clear();
}

void GameProcess::PutStateChangeBuffer(eObjectState nowstate, eObjectState newstate, ParentObject* pObject)
{
	_stateChangeBuffer.push_back(make_tuple(nowstate, newstate ,pObject));
}

GameProcess* GameProcess::s_gameEnginePointer;