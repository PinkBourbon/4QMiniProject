module;
#include <string>
export module aptoCore.Renderable;

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

		DrawType drawType;
		MeshType meshType;
		std::string MeshFilePath;
		std::string TextureFilePath;
		std::string NormalMapFilePath;
		std::string vertexShaderFilePath;
		std::string pixelShaderFilePath;

	private:
		__int64 handle;
	};
}
