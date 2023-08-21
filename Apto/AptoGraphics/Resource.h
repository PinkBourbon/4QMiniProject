#pragma once
#include <string>
#include <iostream>
#include "ResourceMgr.h"

namespace aptoCore
{
	struct IBuilderBase;
	template<typename T> struct IBuilder;


	struct ResourceBase
	{
		friend class ResourceMgr;

		ResourceBase(const IBuilderBase& builder);

		virtual ~ResourceBase()
		{
		}

	protected:
		std::wstring key;
		void* data;
	};

	template<typename Derived>
	struct Resource : ResourceBase
	{
	public:
		Resource(const typename IBuilder<Derived>& builder) : ResourceBase(builder) {}

		void Release()
		{
			if (data)
			{
				if (g_resourceMgr.ReleaseResource(this))
				{
					((Derived*)data)->Release();
				}
				data = nullptr;
			}
		}

		operator Derived* () const
		{
			return (Derived*)data;
		}
	};
}
