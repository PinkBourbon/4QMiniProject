#include "Resource.h"

aptoCore::ResourceBase::ResourceBase(const IBuilderBase& builder) : data(nullptr), key()
{
	data = g_resourceMgr.GetResource(this, builder);
}
