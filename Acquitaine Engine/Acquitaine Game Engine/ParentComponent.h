#pragma once
#include <string>

#include "IComponent.h"

using namespace std;

struct IObject;

class ParentComponent : IComponent
{
public:
	ParentComponent();
	~ParentComponent();

//private:
public:
	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void Awake() override;
	virtual void Enable() override;
	virtual void Start() override;

	virtual void InputEvent() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;

	virtual void Render() override;

	virtual void Disable() override;
	virtual void Release() override;

	virtual void SetGameObject(IObject* parentObject);

private:
	string ComponentName;		// 컴포넌트의 이름
	static int componentIDs;	// 컴포넌트의 ID? 왠지 있어야 할것 같아서.
	int componentID;			// 컴포넌트의 ID.
	IObject* gameObject;		// 내가 소속된 오브젝트
	bool isEnabled;				// 컴포넌트가 활성화 되어 있는지? 아닌지.
};