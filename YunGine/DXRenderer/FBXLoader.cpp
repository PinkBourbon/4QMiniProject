#include "FBXLoader.h"

FbxLoader::FbxLoader()
	: m_pFbxManager(nullptr),
	 m_pFbxImporter(nullptr),
	 m_pFbxScene(nullptr)
{

}

FbxLoader::~FbxLoader()
{

}

void FbxLoader::FbxInit()
{
		m_pFbxManager = FbxManager::Create();
		m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
		m_pFbxScene = FbxScene::Create(m_pFbxManager, "");
}
