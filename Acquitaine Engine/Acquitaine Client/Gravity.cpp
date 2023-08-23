#include "Gravity.h"


Gravity::Gravity(std::string name, act::ParentObject* pObject) :
	_radius(10.0f),
	_force(1.0f)
{
	_componentName = name;
	_gameObject = pObject;
}

void Gravity::Enable()
{

}

void Gravity::Disable()
{

}
