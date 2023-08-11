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
			baseColorTexture(L""), baseColorFactor(1.0f, 1.0f, 1.0f, 1.0f), 
			metallicRoughnessTexture(L""), metallicFactor(1.0f), roughnessFactor(1.0f),
			normalTexture(L""), 
			emissiveTexture(L""), emissiveFactor(0.0f, 0.0f, 0.0f), 
			ambientOcclusionTexture(L""), ambientOcclusionFactor(0.0f, 0.0f, 0.0f),
			alphaMode(AlphaMode::OPAQUE), alphaCutoff(0.5f), isDoubleSided(false)
		{
		}

		wstring baseColorTexture;			// baseColor 텍스쳐가 있을 경우 경로
		Vector4f baseColorFactor;			// baseColor 텍스쳐가 없을 경우 사용될 값
		wstring metallicRoughnessTexture;	// metallicRoughness 텍스쳐가 있을 경우 경로
		float metallicFactor;				// metallicRoughness 텍스쳐가 없을 경우 사용될 값
		float roughnessFactor;				// metallicRoughness 텍스쳐가 없을 경우 사용될 값

		wstring normalTexture;				// normal 텍스쳐가 있을 경우 경로
		wstring emissiveTexture;			// emissive 텍스쳐가 있을 경우 경로
		Vector3f emissiveFactor;			// emissive 텍스쳐가 없을 경우 사용될 값
		wstring ambientOcclusionTexture;	// ambientOcclusion 텍스쳐가 있을 경우 경로
		Vector3f ambientOcclusionFactor;	// ambientOcclusion 텍스쳐가 없을 경우 사용될 값

		AlphaMode alphaMode;				// 알파 모드 기본값은 OPAQUE
		float alphaCutoff;					// 알파 mask 모드에서 해당 수치 이상의 alpha값을 가진 픽셀은 투명해짐. 1.0f 이상이면 머티리얼은 완전 투명
		bool isDoubleSided;					// true시 양면 렌더링
	};
}
