#pragma once
#include "IComponent.h"
#include "IObject.h"

class ParentComponent : IComponent
{
public:
	ParentComponent();
	~ParentComponent();

private:
	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void Awake() override;
	virtual void Enable() override;
	virtual void Start() override;

	virtual void InputEvent() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;

	virtual void Disable() override;
	virtual void Release() override;

	virtual void SetGameObject(IObject* parentObject);

private:
	IObject* gameObject;
};

