#include "GameProcess.h"
#include "TestScene.h"
#include "SceneManager.h"
#include "IObject.h"

import aptoCore.Graphics;



GameProcess::GameProcess()
{
}

GameProcess::~GameProcess()
{
}

void GameProcess::Initialize()
{
	gameEnginePointer = this;

	sceneManager = new SceneManager();
	sceneManager->Initialize();

	bool ret = aptoCore::Graphics::Initialize();

	cout << "Engine Initialized sucess" << endl;
}

void GameProcess::Finalize()
{
	aptoCore::Graphics::Finalize();
}

void GameProcess::RunningGameProcess(double deltaTime)
{
	cout << "Engine is working" << endl;

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
	SceneList.push_back(pscene);
}

void GameProcess::InitializeObjects()
{
	for (auto pObject : waitingObjectList)
	{
		pObject->Initialize();
		PutStateChangeBuffer(ObjectState::START, pObject);
	}
	waitingObjectList.clear();
}

void GameProcess::Awake()
{
	for (auto pObject : awakeObjectList)
	{
		pObject->Awake();
		PutStateChangeBuffer(ObjectState::UPDATE, pObject);
	}
}

void GameProcess::Enable()
{
	for (auto pObject : enableObjectList)
	{
		pObject->Enable();
		PutStateChangeBuffer(ObjectState::UPDATE, pObject);
	}
}

void GameProcess::Start()
{
	for (auto pObject : startObjectList)
	{
		pObject->Start();
		PutStateChangeBuffer(ObjectState::UPDATE, pObject);
	}
}

void GameProcess::InputEvent()
{
	for (auto pObject : awakeObjectList)
	{
		pObject->InputEvent();
	}
}

float GameProcess::FixedUpdate()
{
	///물리연산이 실행되는 부분이고, 실행 시간을 초단위로 반환하도록 구성
	for (auto pObject : awakeObjectList)
	{
		pObject->FixedUpdate();
		pObject->Phsics();
	}

	return 0.0;
}

void GameProcess::Update()
{
	for (auto pObject : updateObjectList)
	{
		pObject->Update();
	}
}

void GameProcess::Render()
{
	for (auto pObject : awakeObjectList)
	{
		pObject->Render();
	}
}

void GameProcess::Disable()
{
	for (auto pObject : disableObjectList)
	{
		pObject->Disable();
	}
}

void GameProcess::Release()
{
	for (auto pObject : releaseObjectList)
	{
		pObject->Release();
	}
}

void GameProcess::ObjectStateChange()
{
	for (auto buff : stateChangeBuffer)
	{
		switch (buff.first)
		{
			case ObjectState::AWAKE:
			{
				awakeObjectList.push_back(buff.second);
			}break;
			case ObjectState::ENABLE:
			{
				enableObjectList.push_back(buff.second);
			}break;
			case ObjectState::START:
			{
				startObjectList.push_back(buff.second);
			}break;
			case ObjectState::UPDATE:
			{
				updateObjectList.push_back(buff.second);
			}break;
			case ObjectState::DISABLE:
			{
				disableObjectList.push_back(buff.second);
			}break;
			case ObjectState::RELEASE:
			{
				releaseObjectList.push_back(buff.second);
			}break;
			default:
			{
			
			}break;
		}
	}
	stateChangeBuffer.clear();
}

void GameProcess::PutStateChangeBuffer(ObjectState state, IObject* pObject)
{
	stateChangeBuffer.push_back(make_pair(state, pObject));
}

GameProcess* GameProcess::gameEnginePointer;