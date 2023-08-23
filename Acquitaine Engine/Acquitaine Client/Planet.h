#pragma once
#include "ParentObject.h"
#include <string>

import apto.math;

class Planet : public act::ParentObject
{
public:
	Planet(const std::string& name);

private:
	float _radius;
};