#pragma once
#include "ParentComponent.h"
#include "../../YunGine/DXRenderer/Renderable.h"

class RenderComponent : public act::ParentComponent
{
public:
	RenderComponent(std::string componentname, act::ParentObject* pObject);
	virtual ~RenderComponent();

	virtual void Awake() override;
	virtual void Enable() override;
	virtual void Start() override;

	virtual void FixedUpdate() override;
	virtual void Update() override;

	virtual void Disable() override;
	virtual void Release() override;

private:
	Renderable* renderObject;
};

