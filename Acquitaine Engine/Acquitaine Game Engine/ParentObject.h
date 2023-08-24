#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "ParentScene.h"

namespace act
{
	class ParentComponent;
	class TestComponent;

	class ParentObject
	{
	public:
		ParentObject();
		virtual ~ParentObject();

	public:
		template<typename T>
		void AddObject(std::string objectName)
		{
			std::cout << "Sucessed object create." << std::endl;
			_includedScene->AddObject<T>(objectName);
		}

		template<typename T> ParentComponent* AddComponent(std::string componentname, ParentObject* thispointer)
		{
			ParentComponent* temp = new T(componentname, thispointer);
			_componentList.push_back(temp);
			return temp;
		}

		template<typename T>
		ParentComponent* GetComponentPointer()
		{
			for (auto pComponent : _componentList)
			{
				T* childComponent = dynamic_cast<T*>(pComponent);
				if (childComponent != nullptr)
				{
					return childComponent;
				}
			}
			return nullptr;
		}

		template<typename T>
		ParentComponent* GetComponentPointer(std::string componentName)
		{
			for (auto pComponent : _componentList)
			{
				if (pComponent->GetComonentName() == componentName)
				{
					return pComponent;
				}
			}
			return nullptr;
		}

		template<typename T>
		std::vector<ParentComponent*>* GetComponentPointers()
		{
			std::vector<ParentComponent*>* temp = new std::vector<ParentComponent*>;
			for (auto pComponent : _componentList)
			{
				T* childComponent = dynamic_cast<T*>(pComponent);
				if (childComponent != nullptr)
				{
					temp->push_back(childComponent);
				}
			}
			return temp;
		}

		std::vector<ParentComponent*>& GetComponentlist();
		void RemoveComponent();
		void SetActive(bool state);
		ParentObject& FindObject(std::string objectname);
		void Delete();

		float GetDeltaTime();

		//private:
	public:
		virtual void Initialize();
		virtual void Finalize();

		virtual void InputEvent();

	public:
		virtual void Awake();
		virtual void Enable();
		virtual void Start();

		virtual void RateUpdate();
		virtual void Update();


		virtual void Disable();
		virtual void Release();

	public:
		bool isEnabled;
		std::string objectName;						// 오브젝트의 이름

	protected:
		static int _objectIDs;					// 이건... 생성자가 호출 될 때마다 자동으로 1씩 더해진다. 그리고 그걸 ID로 삼는다.

		/// 오브젝트의 기초 정보가 저장되어 있는 부분
		int _objectID;							// 실제 이 오브젝트를 구분하는 용도로 쓰일 ID
		std::vector<ParentComponent*> _componentList;		// 오브젝트가 가지고 있는 컴포넌트의 목록

		///소속된 Scene 정보
		ParentScene* _includedScene;
		int _includedSceneID;
	};
}