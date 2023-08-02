#pragma once
#include <windows.h>
#include <string>
#include <fbxsdk.h>
#include "Vertex.h"

/// 디버그와 릴리즈할 떄 라이브러리를 나눠두어야 할까?
/// -23.08.01- Dispact 인재원에서
/// 디버그용과 릴리즈할 때는 꼭 나눠주는게 좋다
/// -23.08.01- Dispact 인재원에서
#ifdef _DEBUG
#pragma comment(lib, "..\\Lib\\debug\\libfbxsdk-md.lib")
#pragma comment(lib, "..\\Lib\\debug\\libxml2-md")
#pragma comment(lib, "..\\Lib\\debug\\zlib-md")
#else
#pragma comment(lib, "..\\Lib\\release\\libfbxsdk-md.lib")
#pragma comment(lib, "..\\Lib\\release\\libxml2-md")
#pragma comment(lib, "..\\Lib\\release\\zlib-md")
#endif
class FbxLoader
{
public:
	FbxLoader();
	~FbxLoader();

	bool FbxInit();
	bool FbxLoad(std::wstring filename);

private:
	FbxManager* _pFbxManager;
	FbxImporter* _pFbxImporter;
	FbxScene* _pFbxScene;
	FbxNode* _pFbxNode;
	FbxCamera* _pFbxCamera;

	DirectX::XMFLOAT3* position;
	DirectX::XMFLOAT3* result;	// we need this variable for save normal information. perhaps?



	bool FbxRelease();
	void NodeProcessRecursive(FbxNode* node);
	void ControlPointProcess(FbxMesh* mesh);
	DirectX::XMFLOAT3 ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCounter);

	void Something(FbxMesh* mesh);

};

