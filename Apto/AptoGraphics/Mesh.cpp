#include "Mesh.h"
#include <d3d11.h>

import aptoCore.rawData.RawMesh;

void aptoCore::Mesh::Release()
{

}

void* aptoCore::MeshBuilder::build() const
{
	aptoCore::RawMesh rawMesh;

	Mesh* mesh = new Mesh();

	if (mesh == nullptr)
	{
		return nullptr;
	}

	return mesh;
}
