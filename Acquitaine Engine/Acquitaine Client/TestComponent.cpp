#include "TestComponent.h"
#include "ParentObject.h"
#include "TestObject_Find.h"


TestComponent::TestComponent(std::string name, act::ParentObject* pObject)
{
	_componentName = name;
	_gameObject = pObject;
}

TestComponent::~TestComponent()
{

}

void TestComponent::Initialize()
{
	std::cout << _gameObject->objectName << " : component Initialize is sucessed." << std::endl;
}

void TestComponent::Finalize()
{

}

void TestComponent::InputEvent()
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
	std::cout << _gameObject->objectName << " : component1 Enable is sucessed." << std::endl;
}

void TestComponent::Start()
{
	std::cout << _gameObject->objectName << " : component Start is sucessed." << std::endl;
	//_gameObject->AddComponent<TestComponent>("testComponent", _gameObject);
	_gameObject->AddObject<TestObject_Find>("createTestObject");
}

void TestComponent::FixedUpdate()
{
}

void TestComponent::Update()
{
	std::cout << _gameObject->objectName << " : component Update is sucessed." << std::endl;
}

void TestComponent::Disable()
{
	std::cout << _gameObject->objectName << " : component2 Disable is sucessed." << std::endl;
}

void TestComponent::Release()
{
}
