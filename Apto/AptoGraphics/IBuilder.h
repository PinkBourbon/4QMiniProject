#pragma once
#include <string>
#include <windows.h>

namespace aptoCore
{
	struct IBuilderBase
	{
		IBuilderBase(const std::wstring& key) : key(key) {}
		virtual void* operator()(std::wstring* typeName) const = 0;
		std::wstring key;
	};

	template<typename Derived>
	struct IBuilder : public IBuilderBase
	{
		using type = Derived;

		IBuilder(const std::wstring& key) : IBuilderBase(key) {}
		virtual void* operator()(std::wstring* typeName) const final
		{
			int wstringLength = MultiByteToWideChar(CP_UTF8, 0, typeid(Derived).name(), -1, nullptr, 0);
			typeName->resize(wstringLength);
			MultiByteToWideChar(CP_UTF8, 0, typeid(Derived).name(), -1, typeName->data(), wstringLength);

			return build();
		}

		virtual void* build() const = 0;
	};

}
