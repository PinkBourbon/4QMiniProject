#pragma once
#include <fbxsdk.h>
#include <unordered_map>

#ifdef _DEBUG
#pragma comment(lib, "..\\Lib\\debug\\libfbxsdk-md.lib")
#pragma comment(lib, "..\\Lib\\debug\\libxml2-md")
#pragma comment(lib, "..\\Lib\\debug\\zlib-md")
#else
#pragma comment(lib, "..\\Lib\\release\\libfbxsdk-md.lib")
#pragma comment(lib, "..\\Lib\\release\\libxml2-md")
#pragma comment(lib, "..\\Lib\\release\\zlib-md")
#endif 

struct vec3
{
	float x;
	float y;
	float z;
};

struct vec2
{
	float x;
	float y;
};

struct Vertex
{
	vec3 position;
	vec3 normal;
	vec2 uv;
	vec3 binormal;
	vec3 tangent;

	// 뭐하는 부분인지 모르겠음
	/*bool operator==(const Vertex& other) const
	{
		return position == other.position && normal == other.normal && uv == other.uv && binormal == other.binormal && tangent == other.tangent;
	}*/
};

class FbxLoaderV2
{
public:
	FbxLoaderV2();
	~FbxLoaderV2();

	void InitializeLoader();
	void LoadFbx(const char* filename);
	void ReleaseLoader();

private:
	vec3* positions;

	FbxManager* manager;
	FbxScene* scene;
	FbxNode* node;
	FbxMesh* mesh;
	FbxCamera* camera;
	FbxImporter* importer;
	FbxNode* rootNode;
	FbxIOSettings* ioset;

	void LoadNodeRecursive(FbxNode* node);
	void ControlPointProcess(FbxMesh* mesh);
	void InsertVertex(const vec3& position, const vec3& normal, const vec2& uv, const vec3& binormal, const vec3& tangent);

	vec3 ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCount);
	vec3 ReadBinormal(FbxMesh* mesh, int controlPointIndex, int vertexCount);
	vec3 ReadTangent(FbxMesh* mesh, int controlPointIndex, int vertexCount);
	vec2 ReadUV(FbxMesh* mesh, int controlPointIndex, int vertexCount);

};