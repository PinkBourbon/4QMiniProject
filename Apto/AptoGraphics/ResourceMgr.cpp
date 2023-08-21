#include "ResourceMgr.h"
#include "Resource.h"
#include "IBuilder.h"

namespace aptoCore
{
	ResourceMgr g_resourceMgr;

	void* ResourceMgr::GetResource(ResourceBase* resource, const IBuilderBase& builder)
	{
		void* data = nullptr;

		std::lock_guard<std::mutex> lock(mutex);
		resource->key = builder.key;
		if (resources.find(builder.key) == resources.end())
		{
			std::wstring typeName;
			data = builder(&typeName);
			resources[builder.key] = { data, typeName };
			//resources.emplace(builder.key, {data, typeName});
		}
		else
		{
			data = resources[builder.key].GetData();
		}


		return data;
	}

	bool ResourceMgr::ReleaseResource(ResourceBase* resource)
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (resources.find(resource->key) != resources.end())
		{
			if (resources[resource->key].Release())
			{
				resources.erase(resource->key);
				return true;
				// 빌더의 Release 를 호출해야함.
			}
		}

		return false;
	}

}
