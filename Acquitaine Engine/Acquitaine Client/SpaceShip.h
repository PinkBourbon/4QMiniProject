#pragma once

#include "ParentObject.h"

import apto.math;

class SpaceShip : public act::ParentObject
{
public:
	SpaceShip();

private:
	apto::Vector2f _startDirection;
	apto::Vector2f _startPosition;
	float _startSpeed;
	float _collisionRadius;
};