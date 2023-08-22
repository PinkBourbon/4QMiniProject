#pragma once
#include "ParentComponent.h"
#include "importGraphics.h"

import aptoCore.Renderable;

class RenderComponent : public act::ParentComponent
{
public:
	RenderComponent(std::string componentname, act::ParentObject* pObject);
	virtual ~RenderComponent();

	virtual void Awake() override;
	virtual void Enable() override;
	virtual void Start() override;

	virtual void RateUpdate() override;
	virtual void Update() override;

	virtual void Disable() override;
	virtual void Release() override;

private:
	aptoCore::Renderable* renderObject;
};

