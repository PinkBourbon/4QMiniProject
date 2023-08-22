#pragma once
#include <fbxsdk.h>
#include <vector>
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

class Model;
class Renderable;
struct ID3D11Buffer;

class FbxLoaderV4
{
public:
	FbxLoaderV4();
	~FbxLoaderV4();

	bool Release();

	void Load(std::string MeshFilePath);

private:
	FbxManager* _manager = nullptr;
	FbxScene* _scene = nullptr;
	::FbxImporter* _importer = nullptr;

	FbxNode* _rootNode = nullptr;
	FbxMesh* _mesh = nullptr;

	FbxAxisSystem _sceneAxisSystem;
	MyVertex* _position = nullptr;

	void SceneSetting();
	void LoadNodeRecursive(FbxNode* node);
	void LoadMesh(FbxMesh* meshl);

	MyVertex ReadNormal(const fbxsdk::FbxMesh* mesh, int controlPointIndex, int vertexCount);
	MyVertex ReadBinormal(FbxMesh* mesh, int controlPointIndex, int vertexCount);
	MyVertex ReadTangent(FbxMesh* mesh, int controlPointIndex, int vertexCount);
	MyTexture ReadUV(FbxMesh* mesh, int controlPointIndex, int vertexCount);

	MyVertex* _positions;

public:
	std::vector<Vertex> _Vertices;
	std::vector<unsigned int>	_Indecies;

	std::vector<Vertex>& GetVertices()
	{
		return _Vertices;
	}

	std::vector<unsigned int>& GetIndecis()
	{
		return _Indecies;
	}

};

