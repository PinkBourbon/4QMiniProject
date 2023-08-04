#include "FbxLoaderV3.h"
#include <cassert>


FbxManager* manager = nullptr;

HRESULT LoadFbx2(std::vector<Vertex3>* pOutVertexVector,const char* fileroot)	// testing
{
	if (!manager)
	{
		manager = FbxManager::Create();

		FbxIOSettings* _pioset = FbxIOSettings::Create(manager, IOSROOT);
		if (!_pioset)
		{
			std::cerr << "Failed to create FbxIOSettings." << std::endl;
			return E_FAIL;
		}
		else
		{
			manager->SetIOSettings(_pioset);
			_pioset->SetBoolProp(IMP_FBX_MATERIAL, true);
			_pioset->SetBoolProp(IMP_FBX_TEXTURE, true);
		}
	}

	FbxImporter* importer = FbxImporter::Create(manager, IOSROOT);
	FbxScene* scene = FbxScene::Create(manager, "");
	//std::string strPath = ws2s(fileroot);

	bool success = importer->Initialize(fileroot, -1, manager->GetIOSettings());
	if (!success)
	{
		return E_FAIL;
	}

	FbxNode* rootNode = scene->GetRootNode();

	if (rootNode)
	{
		for (int i = 0; i < rootNode->GetChildCount(); i++)
		{
			FbxNode* childNode = rootNode->GetChild(i);

			if (childNode->GetNodeAttribute() == NULL)
			{
				continue;
			}

			FbxNodeAttribute::EType AttributeType = childNode->GetNodeAttribute()->GetAttributeType();

			if (AttributeType != FbxNodeAttribute::eMesh)
			{
				continue;
			}

			FbxMesh* mesh = (FbxMesh*)childNode->GetNodeAttribute();

			FbxVector4* vertices = mesh->GetControlPoints();

			for (int j = 0; j < mesh->GetPolygonCount(); j++)
			{
				int iNumVertices = mesh->GetPolygonSize(j);
				if (iNumVertices != 3)
				{
					return E_FAIL;
				}

				for (int k = 0; k < iNumVertices; k++)
				{
					int controlPointIndex = mesh->GetPolygonVertex(j, k);

					Vertex3 vertex;
					vertex.pos[0] = (float)vertices[controlPointIndex].mData[0];
					vertex.pos[1] = (float)vertices[controlPointIndex].mData[1];
					vertex.pos[2] = (float)vertices[controlPointIndex].mData[2];
					pOutVertexVector->push_back(vertex);
				}
			}
		}
	}

	return S_OK;
}

