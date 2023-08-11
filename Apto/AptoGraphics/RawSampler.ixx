module;

export module aptoCore.rawData.RawSampler;

export namespace aptoCore
{
	struct RawSampler
	{
		enum class Filter
		{
			Nearest,
			Linear
		};

		enum class Wrap
		{
			Clamp,
			Repeat,
			Mirror
		};

		Filter minFilter;
		Filter magFilter;
		Wrap wrapS;
		Wrap wrapT;
	};
}
