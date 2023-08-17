#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//#include <assimp/mesh.h>
//#include <assimp/material.h>
//#include <assimp/material.inl>


class AssimpLoader
{
public:
	AssimpLoader();
	~AssimpLoader();

	void LoadFbx(std::wstring FilePath);

private:
	// ai 포맷에 맞춰서 하나 파일패스를 가지고있음
	aiString _aiStrPath;

	aiNode* _node = nullptr;

	void GetData(const aiScene* scene);

	// scene안에 있는 데이터들을 뽑아냄->저장할 방법도 필요 OutPut?
	void GetNode(const aiScene* scene,aiNode* outputNode);
	void GetMesh(const aiScene* scene);
	void GetMaterial(const aiScene* scene);
	void GetTexture(const aiScene* scene);
	void GetLight(const aiScene* scene);

	// void CheckFile(std::string FilePath); // 이미 익스포트해서 뽑은 파일인지를 확인
};



