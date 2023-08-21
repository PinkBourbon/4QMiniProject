#pragma once
#include <unordered_map>
#include <string>
#include <atomic>
#include <mutex>

namespace aptoCore
{
	struct ResourceBase;
	struct IBuilderBase;

	class ResourceMgr
	{
	public:
		ResourceMgr() = default;
		~ResourceMgr()
		{
			CheckManagedData();
		}

	public:
		void* GetResource(ResourceBase* resource, const IBuilderBase& builder);
		bool ReleaseResource(ResourceBase* resource);

	private:
		void CheckManagedData()
		{
			for (const auto& [key, value] : resources)
			{
				wprintf(L"%s, 주소 : 0x%p, refcount : %d\n", value.typeName.c_str(), value.data, value.refCount);
			}
		}

	private:
		struct ManagedData
		{
			ManagedData() : data(nullptr), refCount(0) {}
			ManagedData(void* data, const std::wstring& typeName) : data(data), refCount(1), typeName(typeName) {}

			void* data;
			int refCount;
			std::wstring typeName;

			void* GetData()
			{
				refCount++;
				return data;
			}

			bool Release()
			{
				refCount--;
				if (refCount <= 0)
				{
					return true;
				}
				return false;
			}
		};

		std::unordered_map<std::wstring, ManagedData> resources;
		std::mutex mutex;
	};

	extern ResourceMgr g_resourceMgr;
}
