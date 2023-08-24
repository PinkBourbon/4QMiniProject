#include <windows.h>

#include "GameProcess.h"
#include "importGraphics.h"
#include "ParentObject.h"

namespace act
{

	GameProcess::GameProcess()
		:_deltatime(0)
	{
	}

	GameProcess::~GameProcess()
	{

	}

	void GameProcess::Initialize()
{
		s_gameEnginePointer = this;

		bool ret = ::Initialize();
		std::cout << "Engine Initialized sucess" << std::endl;
	}

	void GameProcess::Finalize()
	{
		::Finalize();
	}

	void GameProcess::RunningGameProcess(double deltaTime)
	{
		std::cout << std::endl << "Engine is working" << std::endl << std::endl;

		/// 스크립팅 할때 보이지 않는 부분ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		ObjectStateChange();

		/// 스크립팅 할때 보이는 부분ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		// 초기화,추가, 시작
		Awake();
		Enable();
		Start();

		// 인풋 입력, 물리연산, 업데이트
		InputEvent(); /// 얘는 스크립팅 할때 보이지 않게 할것.
		Update();
		RateUpdate();

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
		_sceneList.push_back(pscene);
	}

	void GameProcess::ChangeObjectState(ParentObject* pobject, bool state)
	{
		if (state && _objectList.find(pobject)->second != eObjectState::ENABLE)
		{
			PutStateChangeBuffer(eObjectState::ENABLE, pobject);
			std::cout << "Object is activated" << std::endl;
		}
		else if (!state && _objectList.find(pobject)->second != eObjectState::DISABLE)
		{
			PutStateChangeBuffer(eObjectState::DISABLE, pobject);
			std::cout << "Object is unactivated" << std::endl;
		}
	}

	ParentObject& GameProcess::FindObject(std::string objectname)	// 이거 겁나 맘에 안들어!!!!
	{																// 아니 왜 map을 만들어 두고 순회 탐색을 하는거야
																	// 그래서 검색용 map을 따로 만들었습니다.
		auto result = _objectNameList.find(objectname);
		return *result->second;
	}
	void GameProcess::InitializeObjects()
	{
		for (auto pObject : _waitingObjectList)
		{
			pObject->Initialize();
			PutStateChangeBuffer(eObjectState::START, pObject);
		}
		_waitingObjectList.clear();
	}

	void GameProcess::Awake()
	{
		for (auto pObject : _awakeObjectList)
		{
			pObject->Awake();
			PutStateChangeBuffer(eObjectState::UPDATE, pObject);
		}
	}

	void GameProcess::Enable()
	{
		for (auto pObject : _enableObjectList)
		{
			pObject->Enable();
			PutStateChangeBuffer(eObjectState::UPDATE, pObject);
		}
	}

	void GameProcess::Start()
	{
		for (auto pObject : _startObjectList)
		{
			pObject->Start();
			PutStateChangeBuffer(eObjectState::UPDATE, pObject);
		}
	}

	void GameProcess::InputEvent()
	{
		for (auto pObject : _objectList)
		{
			pObject.first->InputEvent();
		}
	}

	void GameProcess::RateUpdate()
{
		for (auto pObject : _updateObjectList)
		{
			pObject->RateUpdate();
		}
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
		::Render(_deltatime);
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
			_objectNameList.erase(_objectNameList.find(pObject->objectName));
			_objectList.erase(_objectList.find(pObject));
			pObject->Release();
			delete pObject;
		}
		_releaseObjectList.clear();
	}

	void GameProcess::ObjectStateChange()
	{
		for (auto buff : _stateChangeBuffer)
		{
			EraseObjectStateList(buff.second);
			switch (buff.first)
			{
				case eObjectState::AWAKE:
				{
					_awakeObjectList.push_back(buff.second);
					_objectList.find(buff.second)->second = eObjectState::AWAKE;
				}break;
				case eObjectState::ENABLE:
				{
					_enableObjectList.push_back(buff.second);
					_objectList.find(buff.second)->second = eObjectState::ENABLE;
				}break;
				case eObjectState::START:
				{
					_startObjectList.push_back(buff.second);
					_objectList.find(buff.second)->second = eObjectState::START;
				}break;
				case eObjectState::UPDATE:
				{
					_updateObjectList.push_back(buff.second);
					_objectList.find(buff.second)->second = eObjectState::UPDATE;
				}break;
				case eObjectState::DISABLE:
				{
					_disableObjectList.push_back(buff.second);
					_objectList.find(buff.second)->second = eObjectState::DISABLE;
				}break;
				case eObjectState::RELEASE:
				{
					_releaseObjectList.push_back(buff.second);
					_objectList.find(buff.second)->second = eObjectState::RELEASE;
				}break;
				default:
				{

				}break;
			}
		}

		_stateChangeBuffer.clear();
	}

	void GameProcess::DeleteObject(ParentObject* pObject)
	{
		PutStateChangeBuffer(eObjectState::RELEASE, pObject);
	}

	void GameProcess::PutStateChangeBuffer(eObjectState newstate, ParentObject* pObject)
	{
		_stateChangeBuffer.push_back(std::make_pair(newstate, pObject));
	}

	void GameProcess::EraseObjectStateList(ParentObject* pObject)
	{
		std::unordered_map<ParentObject*, eObjectState>::iterator temp = _objectList.find(pObject);

		auto tempfunc = [this](std::vector<ParentObject*>& vec, ParentObject* pObject)
		{
			std::vector<ParentObject*>::iterator iter;
			for (iter = vec.begin(); iter != vec.end(); ++iter)
				if (*iter == pObject)
					return iter;
		};
		/// fkaekfh qnsflgkrls goTwlaks

		switch (temp->second)
		{
			case eObjectState::AWAKE:
			{
				_awakeObjectList.erase(tempfunc(_awakeObjectList, pObject));
			}break;
			case eObjectState::ENABLE:
			{
				_enableObjectList.erase(tempfunc(_enableObjectList, pObject));
			}break;
			case eObjectState::START:
			{
				_startObjectList.erase(tempfunc(_startObjectList, pObject));
			}break;
			case eObjectState::UPDATE:
			{
				_updateObjectList.erase(tempfunc(_updateObjectList, pObject));
			}break;
			case eObjectState::DISABLE:
			{
				_disableObjectList.erase(tempfunc(_disableObjectList, pObject));
			}break;
			case eObjectState::RELEASE:
			{
				_releaseObjectList.erase(tempfunc(_releaseObjectList, pObject));
			}break;
			default:
			{

			}break;
		}
	}

	GameProcess* GameProcess::s_gameEnginePointer;
}