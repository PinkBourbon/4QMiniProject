#include "TestComponent 1.h"
#include "TestComponent 2.h"
#include "ParentObject.h"
#include "TransformComponent.h"

TestComponent1::TestComponent1(std::string name, act::ParentObject* pObject)
{
	_componentName = name;
	_gameObject = pObject;
	std::cout << _gameObject->objectName << " : component1 Initialize is sucessed." << std::endl;
}

TestComponent1::~TestComponent1()
{

}

void TestComponent1::Awake()
{
}

void TestComponent1::Enable()
{
	std::cout << _gameObject->objectName << " : component1 Enable is sucessed." << std::endl;
}

void TestComponent1::Start()
{
	std::cout << _gameObject->objectName << " : component1 Start is sucessed." << std::endl;
	TransformComponent* tempcomp = _gameObject->GetComponentPointer<TransformComponent>();
	tempcomp->SetPosition(12.0f, 8.0f, 10.0f);
}

void TestComponent1::RateUpdate()
{
}

void TestComponent1::Update()
{
	std::cout << _gameObject->objectName << " : component1 Update is sucessed." << std::endl;
	//_gameObject->AddComponent<TestComponent2>("test", _gameObject);
	TransformComponent* tempcomp = _gameObject->GetComponentPointer<TransformComponent>();
	tempcomp->SetPosition(tempcomp->GetPosition().x+1, 8.0f, 10.0f);
	std::cout << tempcomp->GetPosition().x << " " << tempcomp->GetPosition().y << " " << tempcomp->GetPosition().z << " " << std::endl;
}

void TestComponent1::Disable()
{
	std::cout << _gameObject->objectName << " : component2 Disable is sucessed." << std::endl;
	_gameObject->SetActive(true);
}

void TestComponent1::Release()
{
}
