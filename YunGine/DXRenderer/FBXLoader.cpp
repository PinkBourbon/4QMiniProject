#include "FBXLoader.h"
#include <vector>

FbxLoader::FbxLoader()
	: _pFbxManager(nullptr),
	_pFbxImporter(nullptr),
	_pFbxScene(nullptr),
	_pFbxNode(nullptr),
	_pFbxCamera(nullptr),
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
	_pFbxManager = FbxManager::Create();

	// IOSetting객체 생성 및 설정이라는데 잘 모르겠다.
	FbxIOSettings* p_IoSetting = FbxIOSettings::Create(_pFbxManager, IOSROOT);
	_pFbxManager->SetIOSettings(p_IoSetting);

	_pFbxImporter = FbxImporter::Create(_pFbxManager, "");
	bool status = _pFbxImporter->Initialize(/*파일이름 or 경로?*/"file.fbx", -1, p_IoSetting);
	if (!status) return false;

	// Create a scene Object named "SceneOne"
	// 씬은 일종의 컨테이너이다.
	_pFbxScene = FbxScene::Create(_pFbxManager, "Scene");
	// fbx파일을 만든씬에 넣어준다.
	_pFbxImporter->Import(_pFbxScene);

	_pFbxNode = FbxNode::Create(_pFbxScene, "NodeOne");

	_pFbxCamera = FbxCamera::Create(_pFbxCamera, "");

	// 임시 fbx노드 생성
	FbxNode* rootNode = _pFbxScene->GetRootNode();
	FbxAxisSystem sceneAxisSystem = _pFbxScene->GetGlobalSettings().GetAxisSystem();
	// 씬내의 좌표축을 바꾸는데 마야로 되어있음(시계방향)
	FbxAxisSystem::MayaYUp.ConvertScene(_pFbxScene);

	// 씬 내에있는 삼각형으로 만들 수 있는 노드는 모두 삼각형화 한다.
	FbxGeometryConverter geometryConverter(_pFbxManager);
	geometryConverter.Triangulate(_pFbxScene, true);

	return true;
}

bool FbxLoader::FbxRelease()
{
	// 역순으로 해제
	_pFbxCamera->Destroy();
	_pFbxNode->Destroy();
	_pFbxScene->Destroy();
	_pFbxImporter->Destroy();
	_pFbxManager->Destroy();

	/*
	if (_pFbxManager)
	{
		_pFbxManager->Destroy();
	}
	// 이런식으로 하면 Manager(관리자)가 관리하는 모든 SDK객체가 파괴된다. 라고하는데 몰?루
	*/

	return true;

}

/// 재귀함수를 이용한 노드 탐색
void FbxLoader::NodeProcessRecursive(FbxNode* node)
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
		NodeProcessRecursive(node->GetChild(i));
	}

	// 이런식으로 사용
	// FbxNode* rootNode = _pFbxScene->GetRootNode();
	// NodeProcess(rootNode);	// 재귀 함수

}


void FbxLoader::ControlPointProcess(FbxMesh* mesh)
{
	unsigned int count = mesh->GetControlPointsCount();
	position = new DirectX::XMFLOAT3[count];

	for (unsigned int i = 0; i < count; ++i)
	{
		// 만약 메쉬제어점 문제가있다면 여기가 문제
		// Vec3* position 처럼 내가 설정한게 아닌 DXMath 의 XMFLOAT3 이용
		// if mesh control point has problem this point is worng
		// 
		position->x = static_cast<float>(mesh->GetControlPointAt(i).mData[0]);
		position->y = static_cast<float>(mesh->GetControlPointAt(i).mData[1]);
		position->z = static_cast<float>(mesh->GetControlPointAt(i).mData[2]);
	}

	// use like this
	// FbxMesh* mesh = node->GetMesh();
	// ProcessControlPoints(mesh);

}


DirectX::XMFLOAT3 FbxLoader::ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCounter)
{
	if (mesh->GetElementNormalCount() < 1)
	{
		// 없을시에 하는 행동
	}

	const FbxGeometryElementNormal* vertexNormal = mesh->GetElementNormal(0);
	DirectX::XMFLOAT3 temp; // for save normal vector

	switch (vertexNormal->GetMappingMode())
	{
		case FbxGeometryElement::eByControlPoint:

			switch (vertexNormal->GetReferenceMode())
			{
				case FbxGeometryElement::eDirect:
				{
					temp.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[0]);
					temp.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[1]);
					temp.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[2]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexNormal->GetIndexArray().GetAt(controlPointIndex);
					temp.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
					temp.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
					temp.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
				}
				break;
				break;
			}

		case FbxGeometryElement::eByPolygonVertex:
			// polygon vertex mapping
			switch (vertexNormal->GetReferenceMode())
			{
				case FbxGeometryElement::eDirect:
				{
					temp.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[0]);
					temp.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[1]);
					temp.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[2]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexNormal->GetIndexArray().GetAt(vertexCounter); // earn index
					temp.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
					temp.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
					temp.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
				}
				break;
				break;
			}
	}
	result = &temp;

}



void FbxLoader::Something(FbxMesh* mesh)
{
	ControlPointProcess(mesh);
	unsigned int triCount = mesh->GetPolygonCount();	// 메쉬의 삼각형 개수를 가져온다.
}

bool FbxLoader::FbxLoad(std::wstring filename)
{
	// 파일 이름을 받아와서 로드
	// 파일 -> 임포터 -> 씬(트리) 해석 -> 매쉬 -> 정보 가져오기 pnct -> 출력

	// 이렇게 넣으면 wstr이 str로 바뀔까?
	std::string temp;
	temp.assign(filename.begin(), filename.end());
	bool bRet = _pFbxImporter->Initialize(temp.c_str());	// 파일명 넘김
	bRet = _pFbxImporter->Import(_pFbxScene);
	FbxAxisSystem::MayaZUp.ConvertScene(_pFbxScene); // 마야 Z축 버전 사용

	if (bRet)
	{
		// fbx는 트리 구조로 이어져있음
		// 재귀호출로 전 순회 가능
		// N 트리 : 지식 개수가 N개임
		//_pRootNode = _pFbxScene->GetRootNode();

	}



	return true;
}

