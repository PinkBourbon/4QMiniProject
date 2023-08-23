#pragma once
#include "ParentComponent.h"
#include <map>

class Gravity;
class SpaceShip;

class GravitySystem : public act::ParentComponent
{
public:
	GravitySystem();

	virtual void Enable() override;
	virtual void Update() override;

	std::map<std::string, Gravity*> gravityMap;
	SpaceShip* ship;
};

