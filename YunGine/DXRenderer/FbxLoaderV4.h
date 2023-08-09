#pragma once

#include <windows.h>
#include <fbxsdk.h>

#include "Vertex.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Lib\\debug\\libfbxsdk-md.lib")
#pragma comment(lib, "..\\Lib\\debug\\libxml2-md.lib")
#pragma comment(lib, "..\\Lib\\debug\\zlib-md.lib")
#else
#pragma comment(lib, "..\\Lib\\release\\libfbxsdk-md.lib")
#pragma comment(lib, "..\\Lib\\release\\libxml2-md.lib")
#pragma comment(lib, "..\\Lib\\release\\zlib-md.lib")
#endif

class FbxLoaderV4
{
public:
	FbxLoaderV4();
	~FbxLoaderV4();

	bool Release();

	bool Load(std::wstring filename);

private:
	FbxManager* _manager = nullptr;
	FbxScene* _scene = nullptr;
	FbxImporter* _importer = nullptr;

	FbxNode* _rootNode = nullptr;
	FbxMesh* _mesh = nullptr;

	FbxAxisSystem _sceneAxisSystem;
	vec3* _position = nullptr;

	void SceneSetting();
	void LoadNodeRecursive(FbxNode* node);
	void ProcessControlPoint(FbxMesh* mesh);
	void InsertVertex(const vec3& position, const vec3& normal, const vec2& uv, const vec3& binormal, const vec3& tangent);

	vec3 ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCount);
	vec3 ReadBinormal(FbxMesh* mesh, int controlPointIndex, int vertexCount);
	vec3 ReadTangent(FbxMesh* mesh, int controlPointIndex, int vertexCount);
	vec2 ReadUV(FbxMesh* mesh, int controlPointIndex, int vertexCount);

};

