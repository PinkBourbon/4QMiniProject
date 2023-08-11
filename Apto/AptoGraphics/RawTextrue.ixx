module;
#include <string>

export module aptoCore.rawData.RawTexture;

import aptoCore.rawData.RawSampler;

export namespace aptoCore
{
	struct RawTexture
	{
		RawTexture() = default;

		using wstring = std::wstring;
		wstring name;
		wstring path;

		RawSampler sampler;
	};
}
