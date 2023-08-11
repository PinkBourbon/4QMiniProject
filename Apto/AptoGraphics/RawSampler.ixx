module;

export module aptoCore.rawData.RawSampler;

export namespace aptoCore
{
	struct RawSampler
	{
		enum class Filter
		{
			Linear,
			Nearest
		};

		enum class Wrap
		{
			Clamp,
			Repeat,
			Mirror
		};

		RawSampler() : 
			minFilter(Filter::Linear),
			magFilter(Filter::Linear),
			wrapU(Wrap::Clamp),
			wrapV(Wrap::Clamp)
		{
		}

		Filter minFilter;
		Filter magFilter;
		Wrap wrapU;
		Wrap wrapV;
	};
}
