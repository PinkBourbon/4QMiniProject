#include "TestComponent.h"
#include "ParentObject.h"
#include "TestObject_Find.h"


TestComponent::TestComponent(string name, act::ParentObject* pObject)
{
	_componentName = name;
	_gameObject = pObject;
}

TestComponent::~TestComponent()
{

}

void TestComponent::Initialize()
{
	cout << _gameObject->objectName << " : component Initialize is sucessed." << endl;
}

void TestComponent::Finalize()
{

}

void TestComponent::InputEvent()
{

}

void TestComponent::Render()
{

}

void TestComponent::Phsics()
{

}

void TestComponent::Awake()
{
}

void TestComponent::Enable()
{
	cout << _gameObject->objectName << " : component1 Enable is sucessed." << endl;
}

void TestComponent::Start()
{
	cout << _gameObject->objectName << " : component Start is sucessed." << endl;
	//_gameObject->AddComponent<TestComponent>("testComponent", _gameObject);
	_gameObject->AddObject<TestObject_Find>("createTestObject");
}

void TestComponent::FixedUpdate()
{
}

void TestComponent::Update()
{
	cout << _gameObject->objectName << " : component Update is sucessed." << endl;
}

void TestComponent::Disable()
{
	cout << _gameObject->objectName << " : component2 Disable is sucessed." << endl;
}

void TestComponent::Release()
{
}
