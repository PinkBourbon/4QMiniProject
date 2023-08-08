#pragma once
#include <vector>

#include "Mesh.h"
#include "TextureLoader.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
class AssimpFbxLoader
{
public:
	AssimpFbxLoader();
	~AssimpFbxLoader();

private:

	bool Load();


};

