#pragma once
#include <string>

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
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ//

		virtual void Awake();
		virtual void Enable();
		virtual void Start();
		virtual void RateUpdate();
		virtual void Update();

		virtual void Disable();
		virtual void Release();

		virtual void SetGameObject(ParentObject* parentObject);
		virtual ParentObject& GetGameObject();

	protected:
		std::string _componentName;		// 컴포넌트의 이름
		ParentObject* _gameObject;	// 내가 소속된 오브젝트
		bool _isEnabled;			// 컴포넌트가 활성화 되어 있는지? 아닌지.

		//	add component가 중간에 생성되면 Initialize 함수를 실행할 방법이 없는데 어떻게 하는게 좋을지 고민 중...
		//	전부 생성자에서 처리하게 한다면 Initialize 함수 자체가 필요 없는거 아닌가?
	};
}