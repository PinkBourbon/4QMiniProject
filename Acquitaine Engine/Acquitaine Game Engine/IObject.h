/// Object의 인터페이스
#pragma once

struct IObject
{
	IObject() {};
	virtual ~IObject() {};

//protected:
public:
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;

	virtual void Awake() = 0;
	virtual void Enable() = 0;
	virtual void Start() = 0;

	virtual void InputEvent() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Phsics() = 0;
	virtual void Update() = 0;

	virtual void Render() = 0;

	virtual void Disable() = 0;
	virtual void Release() = 0;
};