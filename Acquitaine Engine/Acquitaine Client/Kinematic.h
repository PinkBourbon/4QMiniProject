#pragma once
#include "ParentComponent.h"

import apto.math;

/// <summary>
/// 
/// </summary>
class Kinematic : public act::ParentComponent
{
public:
	Kinematic(std::string name, act::ParentObject* pObject);

	virtual void Update() override;

	apto::Vector2f velocity;
};
