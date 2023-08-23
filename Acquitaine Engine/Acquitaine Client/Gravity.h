#pragma once
#include "ParentComponent.h"

class Gravity : act::ParentComponent
{
public:
	Gravity(std::string name, act::ParentObject* pObject);

	virtual void Enable() override;
	virtual void Disable() override;

	float _radius;
	float _force;
};

