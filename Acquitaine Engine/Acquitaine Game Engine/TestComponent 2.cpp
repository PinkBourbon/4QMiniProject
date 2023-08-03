#include "TestComponent 2.h"
#include "ParentObject.h"

TestComponent2::TestComponent2(string name, ParentObject* pObject)
{
	_componentName = name;
	_gameObject = pObject;
}

TestComponent2::~TestComponent2()
{

}

void TestComponent2::Initialize()
{
	cout << _gameObject->objectName << " : component2 Initialize is sucessed." << endl;
}

void TestComponent2::Finalize()
{
}

void TestComponent2::InputEvent()
{
}

void TestComponent2::Render()
{
}

void TestComponent2::Phsics()
{
}

void TestComponent2::Awake()
{
}

void TestComponent2::Enable()
{
}

void TestComponent2::Start()
{
	cout << _gameObject->objectName << " : component2 Start is sucessed." << endl;
}

void TestComponent2::FixedUpdate()
{
}

void TestComponent2::Update()
{
	cout << _gameObject->objectName << " : component2 Update is sucessed." << endl;
}

void TestComponent2::Disable()
{
}

void TestComponent2::Release()
{
}
