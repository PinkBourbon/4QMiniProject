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

bool FbxLoaderV4::Load(std::wstring filename, Model* outModel)
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
	LoadMesh(_mesh);

	// 삼각형 개수 얻기
	_mesh->GetMeshEdgeCount();
	ProcessControlPoint(_mesh);

	Release();

	return false;
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


void FbxLoaderV4::LoadMesh(FbxMesh* mesh)
{
	unsigned int count = mesh->GetControlPointsCount();
	positions = new vec3[count];

	for (unsigned int i = 0; i < count; ++i)
	{
		vec3 position;

		position.x = static_cast<float>(mesh->GetControlPointAt(i).mData[0]);
		position.y = static_cast<float>(mesh->GetControlPointAt(i).mData[1]);
		position.z = static_cast<float>(mesh->GetControlPointAt(i).mData[2]);

		positions[i] = position;
	}

	unsigned int vertexCount = 0;
	unsigned int triCount = mesh->GetPolygonCount();

	for (unsigned int i = 0; i < triCount; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			int controlPointIndex = mesh->GetPolygonVertex(i, j);
			

		}
	}
}

void FbxLoaderV4::ProcessControlPoint(FbxMesh* mesh)
{
	unsigned int count = mesh->GetControlPointsCount();

	vec3 position;
	_position = new vec3[count];

	for (unsigned int i = 0; i < count; ++i)
	{
		position.x = static_cast<float>(mesh->GetControlPointAt(i).mData[0]);
		position.y = static_cast<float>(mesh->GetControlPointAt(i).mData[1]);
		position.z = static_cast<float>(mesh->GetControlPointAt(i).mData[2]);
	}

	//unsigned int triangleCount = mesh->GetPolygonCount();
	unsigned int triangleCount = mesh->GetPolygonVertexCount();
	unsigned int vertexCount = 0;	// 정점의 개수

	for (unsigned int i = 0; i < triangleCount; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			int controlPointIndex = _mesh->GetPolygonVertex(i, j);

			vec3& position = _position[controlPointIndex];

			vec3 normal = ReadNormal(_mesh, controlPointIndex, vertexCount);
			vec3 binormal = ReadBinormal(_mesh, controlPointIndex, vertexCount);
			vec3 tangent = ReadTangent(_mesh, controlPointIndex, vertexCount);

			vec2 uv = ReadUV(_mesh, controlPointIndex, mesh->GetTextureUVIndex(i,j));

			//InsertVertex(position, normal, uv, binormal, tangent);

			vertexCount++;
		}
	}
}

void FbxLoaderV4::InsertVertex(const vec3& position, const vec3& normal, const vec2& uv, const vec3& binormal, const vec3& tangent)
{
	//Vertex vertex = { position, normal, uv, binormal, tangent };
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

vec3 FbxLoaderV4::ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCounter)
{
	if (mesh->GetElementNormalCount() < 1)
	{
		const FbxGeometryElementNormal* vertexNormal = mesh->GetElementNormal(0);

		vec3 result;

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
					break;
				}
				return result;
		}

	}

}

vec3 FbxLoaderV4::ReadBinormal(FbxMesh* mesh, int controlPointIndex, int vertexCounter)
{
	FbxGeometryElementBinormal* vertexBinormal = mesh->GetElementBinormal(0);
	vec3 result; 

	if (vertexBinormal == nullptr)
	{
		return result;
	}

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

vec3 FbxLoaderV4::ReadTangent(FbxMesh* mesh, int controlPointIndex, int vertexCounter)
{
	FbxGeometryElementTangent* vertexTangent = mesh->GetElementTangent(0);
	vec3 result;

	if (vertexTangent == nullptr)
	{
		return result;
	}

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

vec2 FbxLoaderV4::ReadUV(FbxMesh* mesh, int controlPointIndex, int vertexCounter)
{
	FbxGeometryElementUV* vertexUV = mesh->GetElementUV(0);
	vec2 result = { 0.0f, };

	if (vertexUV == nullptr)
	{
		return result;
	}

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
					break;
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
					break;
			}
			break;
	}

	return result;
}
