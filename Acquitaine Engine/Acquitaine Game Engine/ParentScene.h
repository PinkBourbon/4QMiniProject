#pragma once
#include <iostream>
#include <vector>

#include "GameProcess.h"

using namespace std;

struct IObject;

class ParentScene
{
public:
	ParentScene();
	virtual ~ParentScene();
public:
	virtual void Initialize();
	void Finalize();

public:
	template<typename T>
	void AddObject(string objectName)
	{
		cout << "Sucessed object create." << endl;
		_gameProcess->CreateObjects<T>(objectName);
	}

	void FindObject();

protected:
	string _SceneName;
	vector<IObject*>  _inControlObjects;
	GameProcess* const _gameProcess;
	// 이걸 이렇게 쓴 이유? 씬은 구조상 엔진에 접근 할 수 밖에 없는데
	// 굳이 씬마다 포인터를 일일이 재 지정 할 필요는 없을것 같고
	// 동시에 다른 게임 프로세스가 생성되거나 할당되는건 말이 안되므로 const로 설정.
};

/// Scene 도입
//  이전 프로젝트에선 이 Scene이 게임오브젝트나 엔진과 완전히 분리되어 따로 SceneManager에 의해 따로 돌아가는 형태 였지만
//  이번엔 Scene을 분리해서 Scene을 스크립팅 영역으로 삼아보려고 한다.
//  Scene에 CreateObject 함수를 둬서 오브젝트를 생성하고
//  생성된 오브젝트는 Scene의 inControlObjects와 엔진의 ObjectList에 추가됨
//  음... Scene은 inControlObjects들의 오브젝트들을 관리한다.(실제론 엔진에 요청하는거지만)
//  일단은 Scene은 오브젝트를 담아두고 관리하는 중간 단계로 쓸듯.
//  어쨋든 컨텐츠 짜며 게임엔진을 건들 수 없게 하는게 목표.

/// Scene 매니저를 도입하는 것이 맞는가?
//	불필요한 레이어 증가가 아닌지에 관한 문제.
//	일단 모든 씬이 게임 프로세스를 가지는건 피할 수 없다.
//	그리고 씬 매니저를 통해 scene을 통제 한다고 해도 결국은 scene에서 오브젝트에 변동을 준다면 gamaprocess에 도달해야 하는데
//	그러면 결국 const문제를 해결 하지 않고 넘어갈 수는 없다. 어떻게 해야 하는가?