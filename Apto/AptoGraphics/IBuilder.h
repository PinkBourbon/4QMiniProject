#pragma once
#include <string>

namespace aptoCore
{
	struct IBuilderBase
	{
		IBuilderBase(const std::string& key) : key(key) {}
		virtual void* operator()(std::string* typeName) const = 0;
		std::string key;
	};

	template<typename Derived>
	struct IBuilder : public IBuilderBase
	{
		using type = Derived;

		IBuilder(const std::string& key) : IBuilderBase(key) {}
		virtual void* operator()(std::string* typeName) const final
		{
			*typeName = typeid(Derived).name();

			return build();
		}

		virtual void* build() const = 0;
	};

}