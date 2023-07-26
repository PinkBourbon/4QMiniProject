#include "Mesh.h"
#include <d3d11.h>

void aptoCore::Mesh::Release()
{

}

void* aptoCore::MeshBuilder::build() const
{
	Mesh* mesh = new Mesh();

	if (mesh == nullptr)
	{
		return nullptr;
	}

	return mesh;
}
