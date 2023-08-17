/// 4Q에서 사용할 게임엔진
/// 2023.07.20 작성 시작
#pragma once

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>

class IDX11Render;

namespace act
{
	class ParentObject;
	class ParentScene;

	enum class eObjectState
	{
		WAITING,
		AWAKE,
		ENABLE,
		START,
		FIXEDUPDATE,
		UPDATE,
		DISABLE,
		RELEASE
	};

	class GameProcess
	{
	public:
		GameProcess();
		~GameProcess();
	public:
		void GameProcessInitialize();			// 프로그램을 시작할때의 전처리
		void Finalize();			// 프로그램을 종료할때의 후처리
		void RunningGameProcess(double deltaTime);	// 이 함수 내에서 생명주기 함수들이 순서대로 실행된다.

		void AddScene(ParentScene* pscene);

		template<typename T>
		void CreateObjects(std::string objectName, ParentScene* parentscene) // 호출되면 오브젝트를 생성해서 성생대기 리스트에 넣어준다.
		{
			ParentObject* temp = new T(objectName, parentscene);
			_objectList.insert(std::make_pair(temp, eObjectState::WAITING));
			_objectNameList.insert(std::make_pair(objectName, temp));
			_waitingObjectList.insert(temp);
			std::cout << "Sucessed object add list" << std::endl;
		}

		void ChangeObjectState(ParentObject* pobject, bool state);	// 오브젝트의 상태를 바꿀 수 있는 함수. 오브젝트의 Setactive 함수의 도달지점이다.
		// bool 값만 적용해서 Enable, Disable만 설정할 수 있게 했다.

		ParentObject& FindObject(std::string objectname); // 최종적으로 오브젝트, 씬에서 호출한 Find 함수의 도달 지점.
		// 할당된 포인터 값을 바꾸는 일을 막기 위해 참조자로 반환.

		void DeleteObject(ParentObject* pObject);	// 최종적으로 오브젝트에서 실행한 delete 함수가 도달하는 곳.
		// 그러나 사실 이곳에선 오브젝트를 삭제 하지 않는다.
		// 이곳에선 순서적인 절차를 거친 후에 삭제된다.

	private:
		/// 함수들의 실행 주기에 맞춰 함수들을 나열
		/// 각 오브젝트들이 한 프레임에 한번의 상태를 가지도록 하는것이 원칙.
		/// 한 프레임 내에 중복하여 다른 주기함수에서 실행되지 않게 할것.

		void InitializeObjects();	// 생성대기 리스트를 순회해서 Initialize 함수를 호출하고 start로 대기시킨다.(Initialize함수를 밖으로 노출하지 말것)

		void Awake();			// 가장 먼저 실행되는 함수. // 우선적으로 실행되어야 할 오브젝트가 가끔은 있기때문에 존재.
		void Enable();			// enable 상태로 전환된 오브젝트들이 그에 대한 처리가 실행될 함수
		void Start();			// 두번째로 실행되는 함수 - 최초 단 한번만 실행되는 내용이 들어가는 부분.
		// 컨텐츠 스크립트상의 변수는 여기서 초기화 되어도 상관은 없는데, 실제 오브젝트 초기화는 여기서 하지 말것.
		void InputEvent();		// 키, 마우스 등을 인풋 받는 위치
		float FixedUpdate();	// fixedupdatetime을 기반으로 물리연산을 위해 반복 실행되는 업데이트 함수
		void Update();			// 프레임을 기준으로 메 프레임마다 반복 실행되는 업데이트 함수

		void Render();			// 그래픽스가 실제로 랜더링 되는 부분

		void Disable();			// enable 상태가 해제된 오브젝트들이 disable 되었을 때의 처리가 실행될 함수
		void Release();			// 완전히 사용이 종료된 오브젝트들이 실제로 제거되는 부분

		void ObjectStateChange();	// 관리 중인 오브젝트들의 상태를 바꾸어주는 함수. 바뀔 오브젝트 들이 담길 풀을 순회
		// 이건 언젠가 리소스 매니저를 넘겨줘야 하지 않을까?

/// 이건 일단 보조로 두자
		void PutStateChangeBuffer(eObjectState newstate, ParentObject* pObject);
		void EraseObjectStateList(ParentObject* pObject);
		// 관리 중인 오브젝트들의 상태를 바꿔주려고 할때
		// 바로 바꿔주는것은 안되므로 이 함수를 통해 풀에 넣어두고 나중에 바꾼다.
		// 리소스 매니저가 추가된다면 리소스 매니저로 넣어주라는 명령함수만 가지고 있는 놈이 될지도

<<<<<<< HEAD
		HRESULT CreateInitialize();

=======
>>>>>>> pr/16
	public:
		static GameProcess* s_gameEnginePointer;
	private:

		float _deltatime;		// 프레임당 시간
		float _fixedupdatetime;	// fixedUpdate를 위한 고정 실행주기


		std::unordered_map<ParentObject*, eObjectState > _objectList; // 단순히 오브젝트를 담고 있을 리스트. 여기 들어 있는 오브젝트 들은 엔진이 관리 해주는것.
		std::unordered_map< std::string, ParentObject* > _objectNameList; // 위쪽은 내부관리를 위해 쓰는 리스트이고, 이쪽은 외부에서 오브젝트를 검색할 수 있게 만든 맵

<<<<<<< HEAD
		std::unordered_set<ParentObject*> _awakeObjectList;	// Awake State의 오브젝트를 가지고 있는 리스트
		std::unordered_set<ParentObject*> _enableObjectList;	// Enable State의 오브젝트를 가지고 있는 리스트
		std::unordered_set<ParentObject*> _startObjectList;	// Start State의 오브젝트를 가지고 있는 리스트
		std::unordered_set<ParentObject*> _updateObjectList;	// Update State의 오브젝트를 가지고 있는 리스트
		std::unordered_set<ParentObject*> _fixedUpdateObjectList;	// FixedUpdate State의 오브젝트를 가지고 있는 리스트
		std::unordered_set<ParentObject*> _disableObjectList; // Disable State의 오브젝트를 가지고 있는 리스트
		std::unordered_set<ParentObject*> _releaseObjectList; // Release State의 오브젝트를 가지고 있는 리스트
=======
		std::vector<ParentObject*> _awakeObjectList;	// Awake State의 오브젝트를 가지고 있는 리스트
		std::vector<ParentObject*> _enableObjectList;	// Enable State의 오브젝트를 가지고 있는 리스트
		std::vector<ParentObject*> _startObjectList;	// Start State의 오브젝트를 가지고 있는 리스트
		std::vector<ParentObject*> _updateObjectList;	// Update State의 오브젝트를 가지고 있는 리스트
		std::vector<ParentObject*> _fixedUpdateObjectList;	// FixedUpdate State의 오브젝트를 가지고 있는 리스트
		std::vector<ParentObject*> _disableObjectList; // Disable State의 오브젝트를 가지고 있는 리스트
		std::vector<ParentObject*> _releaseObjectList; // Release State의 오브젝트를 가지고 있는 리스트
>>>>>>> pr/16

		std::unordered_set<ParentObject*> _waitingObjectList; // 추가되기 위해 대기중인 오브젝트를 가지고 있는 리스트

		std::vector < std::pair<eObjectState, ParentObject*>> _stateChangeBuffer;

<<<<<<< HEAD
		std::vector <ParentScene*> _SceneList;

		std::unique_ptr<IDX11Render> _renderer;
=======
		std::vector <ParentScene*> _sceneList;
>>>>>>> pr/16
	};
}

/// 이번의 달성 목표에 대해서 정리 해보자면
//   1. 유니티 엔진 처럼 스크립팅 영역과 실제 엔진 구동 영역을 분리.
//   2. dll을 이용해보기
//   3. 멀티 스레딩(로딩창 같은거)
//   4. 기초적인 ECS시스템 구현
//   5. 빌더와 펙토리, 리소스 매니저를 적용해보기
/// 
/// 주저리 주저리는
//	 일단 이전에 오브젝트는 이름을 가지고 찾았지만 이젠 이름대신 아이디를 key값으로 가진다.
//	사용자 입장에서 찾기는 더 어려워 졌지만 사실 이전엔 이름이 같으면 못찾는 문제가 있었으므로 훨씬 나을듯
/// 
//  이제 오브젝트는 껍데기 뿐이고 안에 들어가는 컴포넌트가 메인이 될것... 오브젝트는 ID와 이름만 가지는걸로.
//  어떻게 컴포넌트를 동적으로 받게 할것인가? 컴포넌트의 포인터를 가지는 벡터를 둬야 할까?
/// 
//  그런 의미에서 컴포넌트 또한 생명주기에 따라 구동 될텐데... 이걸 동적으로 오브젝트의 생명주기와 연동시키는 법이 뭐가 있을까?
//  이렇게 되면 오브젝트의 빌더와 펙토리, 컴포넌트의 빌더와 펙토리가 따로 있어야 할거 같은데 이게 맞나?
/// 
//  일단 함수포인터를 적극적으로 써야 할것 같다.XXXXX
//  이젠 아니다! 함수 포인터에서 그 객체가 뭔지 어떻게 알 수 있는가? 하는 문제가 있다.
//	이 문제에 대해서 교수님 께서 추상화와 일반화, 컴포넌트 등의 방법에 대해서 알려주셨고...
//	컴포넌트는 추상화 + 일반화 + RTTI라는데 이건 내가 봤을 때 좀더 찾아봐야 할 것 같고.
//  아니 근데 왜 그생각을 못했지? 잘 모르겠다.
//  그래서 인터페이스를 두고 부모 클래스를 따로 두고 그러는구나.
//  --> 하지만 굳이 그런 방식으로 레이어를 증가 시킬 이유가 없다고 한다. 하지만 인터페이스는 순수해야해!
/// 
//  스크립트 영역은 분리한다고 했지만 다른 언어를 쓸것 같진 않다. 다만 스크립팅 할때 엔진 내부를 직접 건드리지 않도록 하는게 목표.
//  예를 들어, 어떤 물체를 추가 하기 위해 AddCude() 라는 함수를 호출하면 실제론 AddCube 내부에선 Cube라는 오브젝트를 등록하여 달라는 내용을
//  리소스매니저(일단은 엔진)에 보내주고 엔진이 받아뒀다가 만들어서 등록 해주는것. 
/// 
//  유니티라이크 하게 컴포넌트들을 짜서 넣고 컴파일 하면 알아서 등록되면서 돌아가게. 리플렉션은 바라지도 않아.
/// 
/// C++ 20 쓰기로 한거 예시로 제공받은 코루틴 참조해가며 만들면 코루틴은 어렵지 않게 할 수 있을 듯
/// 
/// 일단 순서에 관한 이야기
/// 삭제 순서.
//  일단 해당 프레임에서 삭제되면 안된다.
//  왜냐하면 해당 프레임에서 걔를 찾는 오브젝트가 있을 수 도 있으니까?
//  아마도 그 프레임에선 풀에 넣어놓고 다음 프레임에서 삭제하는게 맞는것 같은데...
//  이전 프로젝트때 그런식으로 모든 상태에 대한 풀을 일일이 만들었던것 같은데 과연 그게 옳은가?
/// 
/// 반대로 추가 순서.
//  추가는 마찬가지로 생산 명령을 가지고 있다가 다음 프레임에 일괄 생산 해주는게 맞다..?
//  다음 프레임인가 프레임 끝인가. 
//  이 문제는 기본적으로 오브젝트가 뭔가 돌아가기 위해선 기본적으로 어떤 상태에 등록되어야 한다는거다.
/// 
/// 그리고 중간에 상태를 바꿔주는 문제.
//  무슨 소리냐면 대표적으로 OnEnable, OnDisable 같은거.
//  물론 얘내들은 스크립팅 할때 곧바로 모습을 드러내주는건 아니지만, 어쨋든 상태를 바꿔달라고 요구하는 거니까...
//  바꿔버렸는데 찾는애가 있으면 곤란하니까 일단 나오고 나서 혹은 다시 들어가기 전에 해야 한다는건데.
//  결론은 셋 모두다 위냐 아래냐의 문제라는건데 정답이 머지..
/// 
//  1. 코드가 실행된다. 실행중 어떤 요청에 의해 상태가 바뀐다.
//  2. 상태가 곧바로 바뀌지 않고 어떤 버퍼에 들어가 상태가 바뀌는 대기 상태로 남는다.
//  3. 다음 프레임에 실제로 상태가 바뀐다. 그리고 실행주기로 들어간다.
/// 
/// 오브젝트를 돌리는 방법에 대해
//  모든 실행주기에 대해 해당하는 오브젝트의 함수를 벡터등에 넣고 돌려버린다고 하면...
//  상태마다 하나씩 있어야 해야 하는데... 자료량이 너무 많아 지지 않나?
//  문제는 또 있다. 그 함수 포인터들을 전부 오브젝트의 실행주기에 맞게 엔진의 배열에서 빼고 넣고 하는게 맞나?
//  상당히 번거로울것 같은데.
//  그래서 대안은 그냥 한다. 혹은 또다른 벡터를 두고 그 상태를 가진 오브젝트만 상태의 벡터에서 돌려주는거?
/// 
//  처음부터 끝까지 직접 박아 버린다면 편하겠지만, 컨텐츠를 완전히 스크립팅 파트로 보내서 분리해 버리고 싶기 때문에
//  스크립트들을 읽어내려서 알아서 추가했으면 좋겠다.
//
/// 스크립트영역을 분리하는걸 어떻게 해야 할지 고민 중이다.
//	지금 문제가 뭐냐면, '오브젝트들에 컴포넌트들을 넣고 컴포넌트에 게임로직을 채운다.(유니티처럼)' 이걸 하고 싶은건데
//  그러면 오브젝트를 추가해야 할때는 어떻게 해야 할까?
//  오브젝트들을 관리 해줄 영역이(분리되어 두가지 형태로) 또 있어야 하는걸까?
//  씬을 추가하고, 씬을 게임 스크립팅을 위한 도화지로 사용하기로 하면서 일단은 해결

// 상태 버퍼 하나일때 문제?
// 상태 버퍼에 들어가는 순서에 차이가 있다는거.
// 안에서 상태를 이렇게 바꿔라! 같은 이야기를 통해 상태 버퍼에 들어갔다고 치자.
// 그러면 밖으로 나오면서 일괄적으로 상태를 바꾸라고 하는 경우가 있을 수 있다.
// 대표적으로 awake나 start는 다음 프레임부터 update에서 동작 해줘야 한다.
// 그러면 일단 상태가 한번 바뀌고 그다음에 상태가 한번 더 바뀐다.
// START 이후에 DISABLE로 가야 하는데 ENABLE로 가는 경우가 생길수도 있다는거지.
// 2학기때는 그래서 모든 바뀔 상태에 대한 컨테이너를 일일이 만들어 줬는데...
// 맘에 안든다. 다른 방법은 없을까?
/// 생각해 보니까 그냥 위에 적으면 되는거 아닌가? 어차피 확정적으로 바뀌는 애들이잖아.
// 미리 상태 변화가 생길거라고 함수 들어오자마자 죄다 버퍼에 넣어버리자.
// 그러면 그 다음에 컨텐츠에서 들어가는게 뒤에 들어갈꺼고 순차적으로 수행되니까 제일 마지막에 있는게 적용되겠지.
/// 다른 오브젝트가 다른 오브젝트의 상태를 건드는거면 어쩌려고? 실행 위치가 달라서 씹힐 수 있잖아.


/// 버전 1의 목표
//	일단 실행주기에 따라 돌아가는 게임엔진을 만드는것과 오브젝트,컴포넌트의 자유로운 추가 삭제.
//  실행주기는 사실 별로 어려울게 없지만 오브젝트 추가와 삭제가 문제다.
//	오브젝트는 다른 오브젝트를 어떻게 알게 할것인가? (아마도 FindObejct같은 함수를 만들어서 엔진이 정보를 넘겨주게 할것 같다.)
//  오브젝트가 다른 오브젝트의 상태를 변환 시키는게 맞는가?
//  엔진은 오브젝트들이 추가되고 삭제되는 것을 어떻게 관리 할 것인가?
//	오브젝트마다 다른 컴포넌들을 포함시키는 것이 가능한가?
//  스크립팅 영역을 분리하는것이 가능한가?
//	*일단 리소스 매니저나 빌더, 팩토리는 의도적으로 제외한다.
//  *어디까지나 엔진에서 쓰이게 될 기능들을 구현해 보는것이 목표

/// 생각나는대로 이거저거 막 하다보니까 너무 파편화 되어 있어서 머가 뭔지 모르겠어!

/// 현재 최대 고민거리
// 오브젝트를 추가하려고 할때 new로 불러오는데, 이때 어떤 타입이 올지 모른다.
// 즉 타입에 대해 알아야 하는데.. 어떻게 할 수 있지?????
// 템플레이트를 쓰기로 했다.

/// 순수 인터페이스 삭제
//	레이어가 많아지니까 개발에 어려움을 겪었다.
//  인터페이스에 있는데 자식에서 구현 안한 함수가 있었는데 난 아예 못찾았고 반장님도 해맸다.
//	C++에서 지원하는 기능인데도 굳이 순수 인터페이스를 사용할 이유가 없다는 내용에 동의해서 제거함.

/// 또 다른 최대 고민거리
//	지금은 오브젝트 리스트가 상태 마다 하나씩 있는 상태
//	이 상태에서 상태가 바뀌면 본인이 있던 리스트에서 빠지고 다음 리스트로 옮겨져야 하는데
//	그렇다면 그냥 검색하면서 빼면 되는거 아닌가? 싶지만 모든 리스트 모든 오브젝트를 순회하게?
//  지금 상태에선 바뀔 상태만 알고 있고 오브젝트가 자신의 상태를 모르기 때문에 모든 리스트를 돌아야 한다.
//  맵, 셋을 쓰면 속도는 줄 수 있겠지만... 여전히 비효율적인건 마찬가지
//	어디서 빼야 할지 모르는것도 문제고, 지금 코드에선 검색해서 빼내는 코드를 넣을 부분도 감이 오지 않는다.
//  무언가 구조적인 변화가 필요한 상황

//	그냥 _stateChangeBuffer가 기존 상태, 바뀔 상태, 오브젝트*를 들고 있는 거면 어떨까?
//	구조적인 변동은 없고 제거되어야 할 리스트도 알고 있다. 여기에 맵, 셋을 쓸 수 도 있을것 같은데.
//	하지만 묘하게 맘에 안드는 부분이 존재. 깔끔하지 않다고 할까.

//	개인적으로 중간에 뭔가(vector)를 하나 거쳐서 정리된 후 넘어가는 형태면 좋을것 같은데 감이 안온다.
//	일단 위의 방법을 사용하기로 했다.

//	하지만 문제가 하나 있는데.. 상태를 바꿔달라는 요청을 외부에서 받았을때,
//  이건 this의 상태 변화 함수가 래핑된 함수를 쓰게 될거란 말이지. 바꾸고자 하는 상태를 알겠지만.(그거로 바꿔야 하니까.)
//	얘는 바꾸려고 하는 오브젝트의 상태를 전혀 모를것 이라는게 문제다.
//	start 안에 작성 될지 update 안에 작성 될지는 알겠지만 그래서 그걸 어떻게 연결 지을 수 있나?
//  언젠가 구조를 또 바꿔야 하겠지만 일단 두고 봐야 할것 같다.

/// 바로 다음날 그 상황에 직면함!!!!
//	오브젝트의 상태를 바꾸고 싶어!!!!
//	근데 그러려면 오브젝	트가 자기가 어떤 상태인지 알아야 해
//	근데 난 오브젝트에게 자기가 어떤 상태인지 모르게 하고 싶어
//	그러면 어떻게 해야 하지? start에서 update가 아니라 disable로 가게 하려면 어떻게 해야 하지???
//	어떻게 짜야 엔진에서 부탁받은 오브젝트가 들어있는 위치를 찾아서 거기서 뺄 수 있는거지?    
//	오브젝트 전체를 담고 있는 리스트가 지금 내가 들고 있는 오브젝트가 어떤 상태 인지 같이 들고 있도록 수정

//	그래서 오브젝트리스를 언 오더드 맵으로 바꾸고 포인터를 키로 이넘을 벨류로 했다.
//	그랬더니 검색할때 문제가 있다.
//	이름으로 찾았더니 기껏 map을 쓰고 있는데 얘를 순회해서 찾고 있다.
//	이거 겁나 맘에 안든다고!!!!
//	그렇다고 검색을 string(objectname)이 아니라 Object의 포인터로 할 수는 없잖아.
//	아예 리스트를 두개를 만들어서 검색을 두번 할까?
//	어차피 O(1) 이잖아.

/// 이상한 문제 발생
//	오브젝트가 다른 오브젝트를 disable 시키도록 했는데, 이상하게 자기 자신을 disable 해버리는 문제를 확인
//	심지어 이 문제는 골치아프게도 있다가 재대로 동작했다가 문제가 있다가 한다.
//	원인이 뭔지 잘 모르겠지만, console 창 출력을 확인 한 결과 SetActive(false)를 자기자신한테 걸고 있는것 같음
//	이름은 일단 중복되지 않는 상태라 자신 자신을 지목하는 문제는 거리가 멀어보임
//	일단 확인 해보니 다른 오브젝트를 disable하는 상태 일때
//	콘솔 출력에 Object is unactivated 라는 문구가 최하단에 뜨는 경우를 제외하면 모두 자기자신을 disable한다.
//	고쳤다! string의 compare 함수는 반환 값이 bool 값이 아니라 int 값이었다.
//	왼쪽이 작으면 음수, 같으면 0, 크다면 양수를 반환한다.

///	씬에 따른 오브젝트 구분을 어떻게 할것인가?
//

/// 일단 오브젝트 관리를 위해 계속 문제가 되는 자료구조 문제부터 보자.

/// 클라이언트를 분리 하면서
//	클라이언트와 게임 프로세스를 어떻게 연결 하는가?
//	클라이언트는 메인 엔트리에 노출하는게 맞는것 같은데 게임엔진은 어떻게 되는가?
//	밖으로 두는게 맞는가? 안으로 묶는게 맞는가?
//	일단 엔트리->클라->게임엔진의 형태로 짜보자