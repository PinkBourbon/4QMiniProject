#pragma once
#include <string>

using namespace std;

namespace act
{

	class ParentObject;

	class ParentComponent
	{
	public:
		ParentComponent();
		virtual ~ParentComponent();

		//private:
	public:
		virtual void Initialize();
		virtual void Finalize();
		virtual void InputEvent();
		virtual void Render();
		virtual void Phsics();
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//

		virtual void Awake();
		virtual void Enable();
		virtual void Start();
		virtual void FixedUpdate();
		virtual void Update();

		virtual void Disable();
		virtual void Release();

		virtual void SetGameObject(ParentObject* parentObject);

	protected:
		string _componentName;		// 컴포넌트의 이름
		int _componentID;			// 컴포넌트의 ID.
		ParentObject* _gameObject;		// 내가 소속된 오브젝트
		bool _isEnabled;			// 컴포넌트가 활성화 되어 있는지? 아닌지.
	};
}