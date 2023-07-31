#pragma once

/// 다양한 곳에서 사용할 매크로를 정의해 놓은 헤더파일
/// static_assert와 assert를 정의해 놓았음.

#ifdef _DEBUG
//#include <string_view>

#define STATIC_ASSERT(condition, message) \
do \
{ \
	static_assert(condition, message); \
} \
while (false)
#else
#define STATIC_ASSERT(condition, message)
#endif // _DEBUG



#ifdef ASSERT
#undef ASSERT
#endif // ASSERT

#ifdef _DEBUG

#include <intrin.h>

#define ASSERT(condition, message) \
do \
{ \
	if (!(condition)) \
	{ \
		::MessageBox(NULL, L""#message, L"Assertion Failed", MB_OK); \
		__debugbreak(); \
	} \
} \
while (false)

#else

#define ASSERT(condition, message)

#endif