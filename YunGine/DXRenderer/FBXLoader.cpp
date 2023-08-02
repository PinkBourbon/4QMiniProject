#include "FBXLoader.h"
#include <vector>

FbxLoader::FbxLoader()
	: m_pFbxManager(nullptr),
	 m_pFbxImporter(nullptr),
	 m_pFbxScene(nullptr),
	m_pFbxNode(nullptr),
	m_pFbxCamera(nullptr),
	position(nullptr)
{

}

FbxLoader::~FbxLoader()
{

}

bool FbxLoader::FbxInit()
{
	// FBX객체의 이름이 고유하지 않으므로 FBX 객체의 이름을 통해 가져오는 기능은 없다.
	// 대신 씬에서 지정된 이름을 가진 모든 객체를 열거하는 코드를 만들 수 있다.

	/// 1번 방법
	m_pFbxManager = FbxManager::Create();

	// IOSetting객체 생성 및 설정이라는데 잘 모르겠다.
	FbxIOSettings* p_IoSetting = FbxIOSettings::Create(m_pFbxManager, IOSROOT);
	m_pFbxManager->SetIOSettings(p_IoSetting);

	m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
	bool status = m_pFbxImporter->Initialize(/*파일이름 or 경로?*/"file.fbx", -1, p_IoSetting);
	if (!status) return false;

	// Create a scene Object named "SceneOne"
	// 씬은 일종의 컨테이너이다.
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "Scene");
	// fbx파일을 만든씬에 넣어준다.
	m_pFbxImporter->Import(m_pFbxScene);

	m_pFbxNode = FbxNode::Create(m_pFbxScene, "NodeOne");

	m_pFbxCamera = FbxCamera::Create(m_pFbxCamera, "");

	// 임시 fbx노드 생성
	FbxNode* rootNode = m_pFbxScene->GetRootNode();
	FbxAxisSystem sceneAxisSystem = m_pFbxScene->GetGlobalSettings().GetAxisSystem();
	// 씬내의 좌표축을 바꾸는데 마야로 되어있음(시계방향)
	FbxAxisSystem::MayaYUp.ConvertScene(m_pFbxScene);

	// 씬 내에있는 삼각형으로 만들 수 있는 노드는 모두 삼각형화 한다.
	FbxGeometryConverter geometryConverter(m_pFbxManager);
	geometryConverter.Triangulate(m_pFbxScene, true);

	return true;
}

bool FbxLoader::FbxRelease()
{
	// 역순으로 해제
	m_pFbxCamera->Destroy();
	m_pFbxNode->Destroy();
	m_pFbxScene->Destroy();
	m_pFbxImporter->Destroy();
	m_pFbxManager->Destroy();

	/*
	if (m_pFbxManager)
	{
		m_pFbxManager->Destroy();
	}
	// 이런식으로 하면 Manager(관리자)가 관리하는 모든 SDK객체가 파괴된다. 라고하는데 몰?루
	*/

	return true;

}

/// 재귀함수를 이용한 노드 탐색
void FbxLoader::NodeProcess(FbxNode* node)
{
	FbxNodeAttribute* nodeAttribute = node->GetNodeAttribute();

	if (nodeAttribute)
	{
		if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			// 노드의 속성이 메쉬이다.
			// 메쉬 작업 수행 부분
			FbxMesh* mesh = node->GetMesh();

		}
	}


	const int childCount = node->GetChildCount();
	for (unsigned int i = 0; i < childCount; ++i)
	{
		NodeProcess(node->GetChild(i));
	}

	//FbxNode* rootNode = m_pFbxScene->GetRootNode();

	//NodeProcess(rootNode);	// 재귀 함수

}


void FbxLoader::ControlPointProcess(FbxMesh* mesh)
{




}

bool FbxLoader::FbxLoad(std::wstring filename)
{
	// 파일 이름을 받아와서 로드
	// 파일 -> 임포터 -> 씬(트리) 해석 -> 매쉬 -> 정보 가져오기 pnct -> 출력

	// 이렇게 넣으면 wstr이 str로 바뀔까?
	std::string temp;
	temp.assign(filename.begin(), filename.end());
	bool bRet = m_pFbxImporter->Initialize(temp.c_str());	// 파일명 넘김
	bRet = m_pFbxImporter->Import(m_pFbxScene);
	FbxAxisSystem::MayaZUp.ConvertScene(m_pFbxScene); // 마야 Z축 버전 사용

	if (bRet)
	{
		// fbx는 트리 구조로 이어져있음
		// 재귀호출로 전 순회 가능
		// N 트리 : 지식 개수가 N개임
		//m_pRootNode = m_pFbxScene->GetRootNode();

	}



	return true;
}

