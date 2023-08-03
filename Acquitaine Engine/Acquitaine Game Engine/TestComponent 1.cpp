#include "TestComponent 1.h"
#include "ParentObject.h"

TestComponent1::TestComponent1(string name, ParentObject* pObject)
{
	_componentName = name;
	_gameObject = pObject;
}

TestComponent1::~TestComponent1()
{

}

void TestComponent1::Initialize()
{
	cout << _gameObject->objectName << " : component1 Initialize is sucessed." << endl;
}

void TestComponent1::Finalize()
{
}

void TestComponent1::InputEvent()
{
}

void TestComponent1::Render()
{
}

void TestComponent1::Phsics()
{
}

void TestComponent1::Awake()
{
}

void TestComponent1::Enable()
{
}

void TestComponent1::Start()
{
	cout << _gameObject->objectName << " : component1 Start is sucessed." << endl;
}

void TestComponent1::FixedUpdate()
{
}

void TestComponent1::Update()
{
	cout << _gameObject->objectName << " : component1 Update is sucessed." << endl;

}

void TestComponent1::Disable()
{
}

void TestComponent1::Release()
{
}
