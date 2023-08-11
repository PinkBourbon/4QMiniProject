/// 
/// 
///
#include "MainProcess.h" 

class GameProcess;
#define MAXLOADSTRING 100

//전역
HINSTANCE hInst;
WCHAR szTitle[MAXLOADSTRING];
WCHAR szWindowClass[MAXLOADSTRING];

int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,
					_In_ LPSTR lpCmdLine, _In_ int nCmdShow){
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	//게임 프로세스 인스턴스 생성
	MainProcess* mainProcess = new MainProcess();

	// 프로세스 초기화
	mainProcess->Initialize(hInstance);

	// 메인 루프
	mainProcess->Loop();

	// 프로그램 종료
	mainProcess->Finalize();

	delete mainProcess;
}