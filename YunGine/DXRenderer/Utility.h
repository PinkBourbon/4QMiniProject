//한글 테스트
//#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
//#include <iostream>
//#include <codecvt>
#include <windows.h>
#include <iostream>
#include <functional>

void wstostr(std::wstring wstr, std::string* outStr)
{
	//std::wstring_convert< std::codecvt_utf8<wchar_t>, wchar_t> converter;
	//*outStr = converter.to_bytes(wstr);

	char str[100] = { 0, };
	WideCharToMultiByte(
		CP_UTF8,
		NULL,
		wstr.c_str(),
		wstr.size(),
		str,
		sizeof(str),
		NULL,
		NULL);

	*outStr = str;
}

void strtowstr(std::string str, std::wstring* outWstr)
{
    //std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    //*outWstr = converter.from_bytes(str);

	wchar_t wchar[100] = { 0, };
	MultiByteToWideChar(
		CP_UTF8,
		NULL,
		str.c_str(),
		str.size(),
		wchar,
		sizeof(wchar));

	*outWstr = wchar;
}
