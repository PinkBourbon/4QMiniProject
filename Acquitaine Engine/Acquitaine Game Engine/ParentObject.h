#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "ParentScene.h"

using namespace std;

namespace act
{
<<<<<<< HEAD

	class ParentScene;
	class ParentComponent;
	class TestComponent;

	class ParentObject
	{
	public:
		ParentObject();
		virtual ~ParentObject();

	public:
		template<typename T>
		void AddComponent(string componentname, ParentObject* thispointer)
		{
			ParentComponent* temp = new T(componentname, thispointer);
			_componentList.push_back(temp);
		}

		template<typename T>
		ParentComponent* GetComponentPointer()
		{
			for (auto pComponent : _componentList)
			{
				if (typeid(pComponent) == typeid(T))
				{
					return pComponent;
				}
			}
			return nullptr;
		}

		vector<ParentComponent*> GetComponentlist();
		void RemoveComponent();
		void SetActive(bool state);
		ParentObject& FindObject(std::string objectname);
		void Delete();

		//private:
	public:
		virtual void Initialize();
		virtual void Finalize();

		virtual void InputEvent();
		virtual void Phsics();
		virtual void Render();

=======
	class ParentComponent;
	class TestComponent;

	class ParentObject
	{
	public:
		ParentObject();
		virtual ~ParentObject();

	public:
		template<typename T>
		void AddObject(string objectName)
		{
			cout << "Sucessed object create." << endl;
			_includedScene->AddObject<T>(objectName);
		}

		template<typename T>
		void AddComponent(string componentname, ParentObject* thispointer)
		{
			ParentComponent* temp = new T(componentname, thispointer);
			_componentList.push_back(temp);
		}

		template<typename T>
		ParentComponent* GetComponentPointer()
		{
			for (auto pComponent : _componentList)
			{
				if (typeid(pComponent) == typeid(T))
				{
					return pComponent;
				}
			}
			return nullptr;
		}

		vector<ParentComponent*> GetComponentlist();
		void RemoveComponent();
		void SetActive(bool state);
		ParentObject& FindObject(std::string objectname);
		void Delete();

		//private:
	public:
		virtual void Initialize();
		virtual void Finalize();

		virtual void InputEvent();
		virtual void Phsics();
		virtual void Render();

>>>>>>> pr/16
	public:
		virtual void Awake();
		virtual void Enable();
		virtual void Start();

		virtual void FixedUpdate();
		virtual void Update();


		virtual void Disable();
		virtual void Release();

	public:
		bool isEnabled;
		string objectName;						// 오브젝트의 이름

	protected:
		static int _objectIDs;					// 이건... 생성자가 호출 될 때마다 자동으로 1씩 더해진다. 그리고 그걸 ID로 삼는다.


		/// 오브젝트의 기초 정보가 저장되어 있는 부분
		int _objectID;							// 실제 이 오브젝트를 구분하는 용도로 쓰일 ID
		vector<ParentComponent*> _componentList;		// 오브젝트가 가지고 있는 컴포넌트의 목록

		///소속된 Scene 정보
		ParentScene* _includedScene;
		int _includedSceneID;
	};

}