#include "AssimpLoader.h"
#include "Utility.h"

AssimpLoader::AssimpLoader()
{

}

AssimpLoader::~AssimpLoader()
{

}

void AssimpLoader::LoadFbx(std::wstring FilePath)
{
	std::string strPath;
	aiString aiStrPath;
	aiStrPath = strPath;
	wstostr(FilePath,&strPath);	// FilePath convert

	Assimp::Importer importer;

	const struct aiScene* scene = importer.ReadFile(strPath,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);;
	
	_node = scene->mRootNode;

	Assimp::IOSystem* IoSystem = nullptr;

	
	GetData(scene);

}

void AssimpLoader::GetData(const aiScene* scene)
{
	GetNode(scene, _node);

	if (scene->HasMeshes())
	{
		GetMesh(scene);
	}

	if (scene->HasMaterials())
	{
		GetMaterial(scene);
	}

	if (scene->HasTextures())
	{
		GetTexture(scene);
	}

	if (scene->HasLights())
	{
		GetLight(scene);
	}

}

void AssimpLoader::GetNode(const aiScene* scene, aiNode* outPutNode)
{
	for (unsigned int i = 0; i < outPutNode->mNumChildren; ++i)
	{
		aiMesh* mesh = scene->mMeshes[outPutNode->mMeshes[i]];
		//mesh
	}

	aiNode* rootNode = scene->mRootNode;
	rootNode->FindNode(_aiStrPath);

}

void AssimpLoader::GetMesh(const aiScene* scene)
{
	//aiMesh* mesh = scene->mMeshes;
}

void AssimpLoader::GetMaterial(const aiScene* scene)
{
	//aiMaterial* material;
}

void AssimpLoader::GetTexture(const aiScene* scene)
{

}

void AssimpLoader::GetLight(const aiScene* scene)
{

}
