#include "KeyFrameData.h"


aptoCore::KeyFrameData::KeyFrameData() :
	pos(),
	MinPosAnimTime(0.0f),
	MaxPosAnimTime(0.0f),
	currPosAnimTime(0.0f),
	lastPosIndex(0),
	rot(),
	MinRotAnimTime(0.0f),
	MaxRotAnimTime(0),
	currRotAnimTime(0),
	lastRotIndex(0)
{

}

apto::Vector3f aptoCore::KeyFrameData::GetPosition()
{
	if (lastPosIndex == 0)
	{
		return pos[0].second;
	}

	apto::Vector3f& nextPos = pos[lastPosIndex].second;
	apto::Vector3f& prevPos = pos[lastPosIndex - 1].second;
	float t = (currPosAnimTime - pos[lastPosIndex - 1].first) / (pos[lastPosIndex].first - pos[lastPosIndex - 1].first);
	return apto::Vector3f::Lerp(prevPos, nextPos, t);
}

apto::Quaternion aptoCore::KeyFrameData::GetQuaternion()
{
	return apto::Quaternion{};
}
