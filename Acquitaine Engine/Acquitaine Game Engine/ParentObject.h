#pragma once
#include <vector>
#include <string>

#include "IObject.h"

using namespace std;

class ParentScene;
class ParentComponent;
class IComponent;

class ParentObject : public IObject
{
public:
	ParentObject();
	virtual ~ParentObject();

public:
	template<typename T>
	void AddComponent()
	{
		IComponent* temp = new T();
		componentList.push_back(temp);
	}

	void RemoveComponent();

//private:
public:
	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void InputEvent() override;
	virtual void Phsics() override;
	virtual void Render() override;
	
public:
	virtual void Awake() override;
	virtual void Enable() override;
	virtual void Start() override;

	virtual void FixedUpdate() override;
	virtual void Update() override;


	virtual void Disable() override;
	virtual void Release() override;

protected:
	static int objectIDs;					// 이건... 생성자가 호출 될 때마다 자동으로 1씩 더해진다. 그리고 그걸 ID로 삼는다.


	/// 오브젝트의 기초 정보가 저장되어 있는 부분
	int objectID;							// 실제 이 오브젝트를 구분하는 용도로 쓰일 ID
	string objectName;						// 오브젝트의 이름
	vector<IComponent*> componentList;		// 오브젝트가 가지고 있는 컴포넌트의 목록
	bool isEnabled;

	///소속된 Scene 정보
	ParentScene* includedScene;
	int includedSceneID;
};

