#include <windows.h>

#include "GameProcess.h"
#include "importGraphics.h"
#include "ParentObject.h"

namespace act
{

	GameProcess::GameProcess()
	{
	}

	GameProcess::~GameProcess()
	{
	}

	void GameProcess::GameProcessInitialize()
	{
		s_gameEnginePointer = this;
#ifdef YUNJINDLLEXPORT
		bool ret = aptoCore::Graphics::Initialize();
#else

#endif


		cout << "Engine Initialized sucess" << endl;
	}

	void GameProcess::Finalize()
	{
		aptoCore::Graphics::Finalize();
	}

	void GameProcess::RunningGameProcess(double deltaTime)
	{
		cout << endl << "Engine is working" << endl << endl;

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
			pObject.first->Render();
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
					_awakeObjectList.insert(buff.second);
					_objectList.find(buff.second)->second = eObjectState::AWAKE;
				}break;
				case eObjectState::ENABLE:
				{
					_enableObjectList.insert(buff.second);
					_objectList.find(buff.second)->second = eObjectState::ENABLE;
				}break;
				case eObjectState::START:
				{
					_startObjectList.insert(buff.second);
					_objectList.find(buff.second)->second = eObjectState::START;
				}break;
				case eObjectState::UPDATE:
				{
					_updateObjectList.insert(buff.second);
					_objectList.find(buff.second)->second = eObjectState::UPDATE;
				}break;
				case eObjectState::DISABLE:
				{
					_disableObjectList.insert(buff.second);
					_objectList.find(buff.second)->second = eObjectState::DISABLE;
				}break;
				case eObjectState::RELEASE:
				{
					_releaseObjectList.insert(buff.second);
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
		_stateChangeBuffer.push_back(make_pair(newstate, pObject));
	}

	void GameProcess::EraseObjectStateList(ParentObject* pObject)
	{
		std::unordered_map<ParentObject*, eObjectState>::iterator temp = _objectList.find(pObject);
		switch (temp->second)
		{
			case eObjectState::AWAKE:
			{
				_awakeObjectList.erase(_awakeObjectList.find(temp->first));
			}break;
			case eObjectState::ENABLE:
			{
				_enableObjectList.erase(_enableObjectList.find(temp->first));
			}break;
			case eObjectState::START:
			{
				_startObjectList.erase(_startObjectList.find(temp->first));
			}break;
			case eObjectState::UPDATE:
			{
				_updateObjectList.erase(_updateObjectList.find(temp->first));
			}break;
			case eObjectState::DISABLE:
			{
				_disableObjectList.erase(_disableObjectList.find(temp->first));
			}break;
			case eObjectState::RELEASE:
			{
				_releaseObjectList.erase(_releaseObjectList.find(temp->first));
			}break;
			default:
			{

			}break;
		}
	}

	HRESULT GameProcess::CreateInitialize()
	{
		HMODULE Module = LoadLibrary(RENDER_PATH);
		if (Module == nullptr)
		{
			return S_FALSE;
		}

		_renderer.reset(reinterpret_cast<IDX11Render * (*)(void)>(GetProcAddress(_module, "CreateRenderer"))());

		if (_renderer == nullptr)
		{
			// 함수 가져오기 실패 처리
			FreeLibrary(_module);
			return S_FALSE;
		}
		else
		{
			// 구체적인 내부 구현이 없으므로 사용할 수 없는 것이다.
			_renderer->Initialize();
		}

		return S_OK;
	}

	GameProcess* GameProcess::s_gameEnginePointer;
}