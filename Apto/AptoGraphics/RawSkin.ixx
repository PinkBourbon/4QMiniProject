export module aptoCore.rawData.RawSkin;

export namespace aptoCore
{
	struct RawSkin
	{
		RawSkin() : 
			boneIndex{ 0, 0, 0, 0 }, 
			boneWeight{ 1.0f, 0.0f, 0.0f, 0.0f } 
		{ }

		unsigned int boneIndex[4];
		float boneWeight[4];
	};
}
