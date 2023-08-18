#include "FbxLoaderV4.h"
#include "Utility.h"

#include "Model.h"
#include "Vertex.h"
#include <vector>
#include <unordered_map>

std::vector<Vertex> vertices;
std::vector<UINT> indices;

//std::unordered_map<Vertex, unsigned int> indexMapping;

FbxLoaderV4::FbxLoaderV4()
{

}

FbxLoaderV4::~FbxLoaderV4()
{
	Release();
}

bool FbxLoaderV4::Release()
{
	_mesh->Destroy();

	_scene->Destroy();
	_importer->Destroy();
	_manager->Destroy();

	return true;
}

void FbxLoaderV4::Load(std::wstring filename, Model* outModel)
{

	// 매니저 생성
	_manager = FbxManager::Create();

	// 설정 객체 생성
	FbxIOSettings* ios = FbxIOSettings::Create(_manager, IOSROOT);
	ios->SetBoolProp(IMP_FBX_MATERIAL, true);

	_manager->SetIOSettings(ios);

	// 파일 변환
	std::string temp;
	wstostr(filename, &temp);

	// 임포터 생성
	_importer = FbxImporter::Create(_manager, "");
	_importer->Initialize(temp.c_str(), -1, ios); // 임포터 초기화

	// 씬 가져오기, importer 초기화 되면 파일에서 씬을 가져오기 위해 씬 컨테이너 생성
	_scene = FbxScene::Create(_manager, "scene");
	_importer->Import(_scene);

	SceneSetting();

	// 노드 가져오기
	LoadNodeRecursive(_rootNode);

	// 메쉬 불러오기
	LoadMesh(_mesh, outModel);

	_importer->Destroy();
}

void FbxLoaderV4::SceneSetting()
{
	// 씬의 루트노드 설정
	_rootNode = _scene->GetRootNode();

	// 좌표축 가져오기
	_sceneAxisSystem = _scene->GetGlobalSettings().GetAxisSystem();

	// 씬 내의 좌표축을 바꿔준다.
	FbxAxisSystem::MayaZUp.ConvertScene(_scene);

	// 씬 내에서 삼각형화 할 수 있는 모든 노드를 삼각형화 시킴
	FbxGeometryConverter geometryConverter(_manager);
	geometryConverter.Triangulate(_scene, true);
}

void FbxLoaderV4::LoadNodeRecursive(FbxNode* node)
{
	FbxNodeAttribute* nodeAttribute = node->GetNodeAttribute();
	if (nodeAttribute)
	{
		if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			// 메쉬 속성을 가지고있는 노드라면 메쉬에 대한 작업을 수행한다.
			_mesh = node->GetMesh();
		}
	}

	const int childCount = node->GetChildCount();
	for (unsigned int i = 0; i < childCount; ++i)
	{
		LoadNodeRecursive(node->GetChild(i));
	}
}

void FbxLoaderV4::LoadMesh(FbxMesh* mesh, Model* outModel)
{
	unsigned int count = mesh->GetControlPointsCount();
	_positions = new MyVertex[count];

	for (unsigned int i = 0; i < count; ++i)
	{
		MyVertex position;

		position.x = static_cast<float>(mesh->GetControlPointAt(i).mData[0]);
		position.y = static_cast<float>(mesh->GetControlPointAt(i).mData[1]);
		position.z = static_cast<float>(mesh->GetControlPointAt(i).mData[2]);

		_positions[i] = position;
	}

	unsigned int vertexCount = 0;
	unsigned int triCount = mesh->GetPolygonCount();

	for (unsigned int i = 0; i < triCount; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			int controlPointIndex = mesh->GetPolygonVertex(i, j);
			_Vertices.emplace_back(Vertex());
			_Vertices[i * 3 + j].pos = _positions[controlPointIndex];
			_Vertices[i * 3 + j].normal = ReadNormal(mesh, controlPointIndex, vertexCount);
			_Vertices[i * 3 + j].uv = ReadUV(mesh, controlPointIndex, mesh->GetTextureUVIndex(i, j));
			_Vertices[i * 3 + j].binormal = ReadBinormal(mesh, controlPointIndex, vertexCount);
			_Vertices[i * 3 + j].tangent = ReadTangent(mesh, controlPointIndex, vertexCount);

			vertexCount++;

		}
		_Indecies.push_back(i * 3);
		_Indecies.push_back(i * 3 + 1);
		_Indecies.push_back(i * 3 + 2);
	}

	delete[] _positions;
	_positions = nullptr;

}

MyVertex FbxLoaderV4::ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCounter)
{
	if (mesh->GetElementNormalCount() < 1)
	{
		std::cout << "No Normals" << std::endl;
	}

	const FbxGeometryElementNormal* vertexNormal = mesh->GetElementNormal(0);

	MyVertex result;

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
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			// polygon vertex mapping
			switch (vertexNormal->GetReferenceMode())
			{
				case FbxGeometryElement::eDirect:
				{
					result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[0]);
					result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[1]);
					result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[2]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexNormal->GetIndexArray().GetAt(vertexCounter); // 인덱스를 얻어온다.
					result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
					result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
					result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
				}
				break;
			}
			break;
	}
	return result;

}

MyVertex FbxLoaderV4::ReadBinormal(FbxMesh* mesh, int controlPointIndex, int vertexCounter)
{
	FbxGeometryElementBinormal* vertexBinormal = mesh->GetElementBinormal(0);
	if (!vertexBinormal || vertexBinormal->GetMappingMode() == FbxGeometryElement::eNone)
	{
		return MyVertex();
	}

	MyVertex result;

	/// 이부분에서 null
	/// null이 나오는 이유-> 가져오려고 하는 정보가 fbx파일에 없을시에는 null값이 나옴
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
					break;
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
					break;

			}
			break;
	}

	return result;
}

MyVertex FbxLoaderV4::ReadTangent(FbxMesh* mesh, int controlPointIndex, int vertexCounter)
{
	FbxGeometryElementTangent* vertexTangent = mesh->GetElementTangent(0);

	if (!vertexTangent || vertexTangent->GetMappingMode() == FbxGeometryElement::eNone)
	{
		return MyVertex();
	}

	MyVertex result;

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
					break;
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
					break;
			}
			break;
	}


	return result;
}

MyTexture FbxLoaderV4::ReadUV(FbxMesh* mesh, int controlPointIndex, int vertexCounter)
{
	const FbxGeometryElementUV* texture = mesh->GetElementUV(0);

	if (!texture || texture->GetMappingMode() == FbxGeometryElement::eNone)
	{
		return MyTexture();
	}

	FbxVector2 uv = mesh->GetElementUV()->GetDirectArray().GetAt(vertexCounter);

	MyTexture result;

	result.u = static_cast<float>(texture->GetDirectArray().GetAt(vertexCounter).mData[0]);
	result.v = 1.0f - static_cast<float>(texture->GetDirectArray().GetAt(vertexCounter).mData[1]);

	return result;

}


