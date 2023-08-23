#pragma once
#include "ParentObject.h"
#include <string>

import apto.math;

class Planet : public act::ParentObject
{
public:
	Planet(std::string name, act::ParentScene* parentScene);

private:
	float _radius;
};