#pragma once
struct IComponent
{
	IComponent() {}
	virtual ~IComponent() {}

protected:
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;

	virtual void Awake() = 0;
	virtual void Enable() = 0;
	virtual void Start() = 0;

	virtual void InputEvent() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Update() = 0;

	virtual void Disable() = 0;
	virtual void Release() = 0;
};
