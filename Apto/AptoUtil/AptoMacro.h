#pragma once
#include <windows.h>

/// 다양한 곳에서 사용할 매크로를 정의해 놓은 헤더파일
/// static_assert와 assert를 정의해 놓았음.

#ifdef _DEBUG

#define APTO_STATIC_ASSERT(condition, message) \
do \
{ \
	static_assert(condition, message); \
} \
while (false)

#else

#define APTO_STATIC_ASSERT(condition, message)

#endif // _DEBUG



//#ifdef APTO_ASSERT
//#undef APTO_ASSERT
//#endif // APTO_ASSERT

#ifdef _DEBUG

#define APTO_ASSERT(condition, message) \
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

#define APTO_ASSERT(condition, message)

#endif
