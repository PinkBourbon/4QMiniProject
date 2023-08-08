module;
#include <string>

export module aptoCore.rawData.RawMaterial;

import apto.math.Vector4f;
import apto.math.Vector3f;

export namespace aptoCore
{
	struct RawMaterial
	{
		using Vector4f = apto::Vector4f;
		using Vector3f = apto::Vector3f;
		using wstring = std::wstring;

		enum class AlphaMode
		{
			OPAQUE,
			MASK,
			BLEND
		};

		RawMaterial() :
			baseColor(L""), baseColorFactor(1.0f, 1.0f, 1.0f, 1.0f), 
			metallicRoughnessTexture(L""), metallicFactor(1.0f), roughnessFactor(1.0f),
			normalTexture(L""), emissiveTexture(L""), emissiveFactor(0.0f, 0.0f, 0.0f), ambientOcclusionTexture(L""),
			alphaMode(AlphaMode::OPAQUE), alphaCutoff(0.5f), isDoubleSided(false)
		{

		}
		wstring baseColor;
		Vector4f baseColorFactor;
		wstring metallicRoughnessTexture;
		float metallicFactor;
		float roughnessFactor;

		wstring normalTexture;
		wstring emissiveTexture;
		Vector3f emissiveFactor;
		wstring ambientOcclusionTexture;

		AlphaMode alphaMode;			// 알파 모드
		float alphaCutoff;				// 알파 mask 모드에서 해당 수치 이상의 alpha값을 가진 픽셀은 투명해짐. 1.0f 이상이면 머티리얼은 완전 투명
		bool isDoubleSided;				// true시 양면 렌더링
	};
}
