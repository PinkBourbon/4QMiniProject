#include "FbxLoaderV2.h"
#include <iostream>
#include <vector>

std::vector<Vertex> vertices;
std::vector<unsigned int> indices;

// 커스텀으로 만든 자료형을 key값으로 넘겨주려고 하면
// key를 해쉬화 할 수 있도록 해줘야 한다.
//std::unordered_map<Vertex, unsigned int> indexMapping;

FbxLoaderV2::FbxLoaderV2() :
	positions(nullptr),
	manager(nullptr),
	scene(nullptr),
	node(nullptr),
	mesh(nullptr),
	camera(nullptr),
	importer(nullptr),
	rootNode(nullptr),
	ioset(nullptr)
{
	InitializeLoader();
}

FbxLoaderV2::~FbxLoaderV2()
{

}

void FbxLoaderV2::InitializeLoader()
{
	manager = FbxManager::Create();
	scene = FbxScene::Create(manager, "FirstScene");
	node = FbxNode::Create(scene, "FirstNode");
	mesh = FbxMesh::Create(scene, "");

	FbxCamera* camera = FbxCamera::Create(scene, "");
	FbxCameraManipulator* cameraManipulator = FbxCameraManipulator::Create(manager, "");

	/// 중간 세팅
	ioset = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(ioset);

}

void FbxLoaderV2::LoadFbx(const char* filename)
{
	// 임포터 생성
	importer = FbxImporter::Create(manager, "");

	// importer 초기화
	bool status = importer->Initialize(filename, -1, manager->GetIOSettings());

	if (!status)
	{
		exit(-1);
	}

	importer->Import(scene);

	/// 노드 세팅
	rootNode = scene->GetRootNode();

	/// 루트노드에서 자식노드를 가져옴
	LoadNodeRecursive(rootNode);

	/// 좌표축 가져오기
	FbxAxisSystem sceneAxisSystem = scene->GetGlobalSettings().GetAxisSystem();

	/// 씬 내의 좌표축 변경
	FbxAxisSystem::MayaYUp.ConvertScene(scene);

	FbxGeometryConverter geometryConverter(manager);
	geometryConverter.Triangulate(scene, true);

	/// 메쉬정보 가져오기
	mesh = node->GetMesh();
	ControlPointProcess(mesh);
	unsigned int triangleCount = mesh->GetPolygonCount();	// 메쉬의 삼각형 개수 가져오기
	unsigned int vertexCount = 0;

	for (unsigned int i = 0; i < triangleCount; ++i)	// 삼각형의 개수
	{
		for (unsigned int j = 0; j < 3; ++j)		//삼각형은 세개의 점을가지고있음
		{
			int controlPointIndex = mesh->GetPolygonVertex(i, j);	// 제어점 인덱스를 가져옴

			vec3& position = positions[controlPointIndex];	// 현재 정점에 대한 위치

			vec3 normal = ReadNormal(mesh, controlPointIndex, vertexCount);	//노말벡터
			vec3 binormal = ReadBinormal(mesh, controlPointIndex, vertexCount);
			vec3 tangent = ReadTangent(mesh, controlPointIndex, vertexCount);

			vec2 uv = ReadUV(mesh, controlPointIndex, mesh->GetTextureUVIndex(i, j));

			InsertVertex(position, normal, uv, binormal, tangent);

			vertexCount++;	// 정점의 개수
		}
	}
}

void FbxLoaderV2::ReleaseLoader()
{
	// Destroy these objects
	ioset->Destroy();
	rootNode->Destroy();
	importer->Destroy();
	camera->Destroy();	//세세한 것도 해제해줘야할까? 아니면 매니저를 없애면 모두 없어질까?

	mesh->Destroy();      // Destroy the mesh
	node->Destroy();      // Destroy the node
	scene->Destroy();     // Destroy the scene and its objects
	
	manager->Destroy(); // Destroy SDK Manager and its objects

	if (manager)
	{
		manager->Destroy();
	}
}

void FbxLoaderV2::LoadNodeRecursive(FbxNode* node)
{
	FbxNodeAttribute* nodeAttribute = node->GetNodeAttribute();

	if (nodeAttribute)
	{
		if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			// This node properti is mesh
			// do work about mesh

			// FbxMesh로 캐스팅된 노드 속성의 포인터를 가져온다.
			FbxMesh* mesh = node->GetMesh();
		}
	}

	const int childCount = node->GetChildCount();
	for (unsigned int i = 0; i < childCount; ++i)
	{
		LoadNodeRecursive(node->GetChild(i));
	}
}

void FbxLoaderV2::ControlPointProcess(FbxMesh* mesh)
{
	// 제어점의 개수를 가져온다.
	unsigned int count = mesh->GetControlPointsCount();
	positions = new vec3[count];

	for (unsigned int i = 0; i < count; ++i)
	{
		vec3 position;

		// 제어점을 가져오려면 GetControlPointAt(int index) 멤버 함수를 이용한다.
		position.x = static_cast<float>(mesh->GetControlPointAt(i).mData[0]); // x좌표
		position.y = static_cast<float>(mesh->GetControlPointAt(i).mData[1]); // y좌표
		position.z = static_cast<float>(mesh->GetControlPointAt(i).mData[2]); // z좌표
	}
}

void FbxLoaderV2::InsertVertex(const vec3& position, const vec3& normal, const vec2& uv, const vec3& binormal, const vec3& tangent)
{
	Vertex vertex = { position, normal, uv, binormal, tangent };
	//auto lookup = indexMapping.find(vertex);
	//if (lookup != indexMapping.end())
	//{
	//	indices.push_back(lookup->second);
	//}
	//else
	//{
	//	unsigned int index = vertices.size();
	//	indexMapping[vertex] = index;
	//	indices.push_back(index);
	//	vertices.push_back(vertex);
	//}
}

vec3 FbxLoaderV2::ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCount)
{
	//if (mesh->GetElementBinormalCount() < 1)
	//{
	//	exit();
	//}
	// 터질리없다고 생각하고 주석처리

	const FbxGeometryElementNormal* vertexNormal = mesh->GetElementNormal(0);	// 노말 가져오기

	vec3 result;	// 노말벡터를 저장할 벡터

	switch (vertexNormal->GetMappingMode())
	{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexNormal->GetReferenceMode())
			{
				case FbxGeometryElement::eDirect:
				{
					result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[0]);
					result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[1]);
					result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[2]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexNormal->GetIndexArray().GetAt(controlPointIndex); // 인덱스를 얻어온다.
					result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
					result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
					result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
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
					result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCount).mData[0]);
					result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCount).mData[1]);
					result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCount).mData[2]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexNormal->GetIndexArray().GetAt(vertexCount); // 인덱스를 얻어온다.
					result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
					result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
					result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
				}
				break;
				break;
			}
			return result;

	}
}

vec3 FbxLoaderV2::ReadBinormal(FbxMesh* mesh, int controlPointIndex, int vertexCounter)
{
	FbxGeometryElementBinormal* vertexBinormal = mesh->GetElementBinormal(0);
	vec3 result;

	switch (vertexBinormal->GetMappingMode())
	{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexBinormal->GetReferenceMode())
			{
				case FbxGeometryElement::eDirect:
				{
					result.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(controlPointIndex).mData[0]);
					result.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(controlPointIndex).mData[1]);
					result.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(controlPointIndex).mData[2]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexBinormal->GetIndexArray().GetAt(controlPointIndex);
					result.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[0]);
					result.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[1]);
					result.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[2]);
				}
				break;
				default:
					std::cout << "Error: Invalid vertex reference mode!" << std::endl;
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexBinormal->GetReferenceMode())
			{
				case FbxGeometryElement::eDirect:
				{
					result.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(vertexCounter).mData[0]);
					result.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(vertexCounter).mData[1]);
					result.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(vertexCounter).mData[2]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexBinormal->GetIndexArray().GetAt(vertexCounter);
					result.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[0]);
					result.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[1]);
					result.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[2]);
				}
				break;
				default:
					std::cout << "Error: Invalid vertex reference mode!" << std::endl;
			}
			break;
	}

	return result;
}

vec3 FbxLoaderV2::ReadTangent(FbxMesh* mesh, int controlPointIndex, int vertexCounter)
{
	FbxGeometryElementTangent* vertexTangent = mesh->GetElementTangent(0);
	vec3 result;

	switch (vertexTangent->GetMappingMode())
	{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexTangent->GetReferenceMode())
			{
				case FbxGeometryElement::eDirect:
				{
					result.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(controlPointIndex).mData[0]);
					result.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(controlPointIndex).mData[1]);
					result.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(controlPointIndex).mData[2]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexTangent->GetIndexArray().GetAt(controlPointIndex);
					result.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[0]);
					result.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[1]);
					result.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[2]);
				}
				break;
				default:
					std::cout << "Error: Invalid vertex reference mode!" << std::endl;
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexTangent->GetReferenceMode())
			{
				case FbxGeometryElement::eDirect:
				{
					result.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(vertexCounter).mData[0]);
					result.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(vertexCounter).mData[1]);
					result.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(vertexCounter).mData[2]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexTangent->GetIndexArray().GetAt(vertexCounter);
					result.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[0]);
					result.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[1]);
					result.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[2]);
				}
				break;
				default:
					std::cout << "Error: Invalid vertex reference mode!" << std::endl;
			}
			break;
	}


	return result;
}

vec2 FbxLoaderV2::ReadUV(FbxMesh* mesh, int controlPointIndex, int vertexCounter)
{
	FbxGeometryElementUV* vertexUV = mesh->GetElementUV(0);
	vec2 result;

	switch (vertexUV->GetMappingMode())
	{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexUV->GetReferenceMode())
			{
				case FbxGeometryElement::eDirect:
				{
					result.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(controlPointIndex).mData[0]);
					result.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(controlPointIndex).mData[1]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexUV->GetIndexArray().GetAt(controlPointIndex);
					result.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[0]);
					result.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[1]);
				}
				break;
				default:
					std::cout << "Error: Invalid vertex reference mode!" << std::endl;
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexUV->GetReferenceMode())
			{
				case FbxGeometryElement::eDirect:
				{
					result.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(vertexCounter).mData[0]);
					result.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(vertexCounter).mData[1]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexUV->GetIndexArray().GetAt(vertexCounter);
					result.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[0]);
					result.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[1]);
				}
				break;
				default:
					std::cout << "Error: Invalid vertex reference mode!" << std::endl;
			}
			break;
	}

	return result;
}

