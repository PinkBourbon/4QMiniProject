module;
#include <string>
export module aptoCore.Renderable;

export namespace apto
{
	class Transform;
}

export namespace aptoCore
{
	struct Renderable
	{
	public:
		enum class DrawType
		{
			WireFrame,
			Solid
		};
		enum class MeshType
		{
			SkinnedMesh,
			StaticMesh
		};

		apto::Transform* objectTransform;

		DrawType drawType;
		MeshType meshType;
		std::string objectName;
		std::string MeshFilePath;
		std::string TextureFilePath;
		std::string NormalMapFilePath;
		std::string vertexShaderFilePath;
		std::string pixelShaderFilePath;

		__int64 handle;
	};
}
