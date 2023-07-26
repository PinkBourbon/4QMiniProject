#include "GameProcess.h"

GameProcess::GameProcess()
{
}

GameProcess::~GameProcess()
{
}

void GameProcess::Initialize()
{
}

void GameProcess::Finalize()
{
}

void GameProcess::RunningGameProcess()
{
	float fixedupdateTimeRate = 0;

	/// 스크립팅 할때 보이지 않는 부분ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	PutStateChangeBuffer();
	
	/// 스크립팅 할때 보이는 부분ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	// 초기화,추가, 시작
	Awake();
	Enable();
	Start();

	// 인풋 입력, 물리연산, 업데이트
	InputEvent(); /// 얘는 스크립팅 할때 보이지 않게 할것.
	while (fixedupdateTimeRate > FixedUpdate());	//물리연산이 들어간 부분. 실행시간이 fixedupdatetime보다 작다면 픽스드 업데이트를 반복 실행한다.
	Update();

	// 비활성화, 사용 종료
	Disable();
	Release();

	/// 스크립팅 할때 보이지 않는 부분ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	CreateObjects();
	InitializeObjects();
}

void GameProcess::CreateObjects()
{
}

void GameProcess::InitializeObjects()
{
}

void GameProcess::Awake()
{
}

void GameProcess::Enable()
{
}

void GameProcess::Start()
{
}

void GameProcess::InputEvent()
{
}

float GameProcess::FixedUpdate()
{
	///물리연산이 실행되는 부분이고, 실행 시간을 초단위로 반환하도록 구성
}

void GameProcess::Update()
{
}

void GameProcess::Render()
{
}

void GameProcess::Disable()
{
}

void GameProcess::Release()
{
}

void GameProcess::ObjectStateChange()
{
}

void GameProcess::PutStateChangeBuffer()
{
}
