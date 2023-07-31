#pragma once
#include <windows.h>
#include <fbxsdk.h>

class FbxLoader
{
public:
	FbxLoader();
	~FbxLoader();

private:
	FbxManager* m_pFbxManager;
	FbxImporter* m_pFbxImporter;
	FbxScene* m_pFbxScene;

	void FbxInit();


};

