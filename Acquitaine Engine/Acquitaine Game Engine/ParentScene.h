#pragma once
#include <vector>

#include "IObject.h"

using namespace std;

class ParentScene
{
public:
	ParentScene();
	~ParentScene();

public:
	void AddObject();
	void RemoveObject();
	void ChangeObjectState();

private:
	vector<IObject*>  inControlObjects;
};

/// Scene 도입
//  이전 프로젝트에선 이 Scene이 게임오브젝트나 엔진과 완전히 분리되어 따로 SceneManager에 의해 따로 돌아가는 형태 였지만
//  이번엔 Scene을 분리해서 Scene을 스크립팅 영역으로 삼아보려고 한다.
//  Scene에 CreateObject 함수를 둬서 오브젝트를 생성하고
//  생성된 오브젝트는 Scene의 inControlObjects와 엔진의 ObjectList에 추가됨
//  음... Scene은 inControlObjects들의 오브젝트들을 관리한다.(실제론 엔진에 요청하는거지만)
//  일단은 Scene은 오브젝트를 담아두고 관리하는 중간 단계로 쓸듯.
//  어쨋든 컨텐츠 짜며 게임엔진을 건들 수 없게 하는게 목표.