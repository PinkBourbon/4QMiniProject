#include <iostream>
#include "Vertex.h"
#include "AptoMacro.h"


import apto.math;
import apto.util.Time;
import apto.graphics.Camera;
import aptoCore.Graphics;

bool isResize = false;

int main()
{

#ifdef _WIN32
	//SetConsoleOutputCP(CP_UTF8);
	//std::locale loc = std::wcout.imbue(std::locale("korean"));
	//setlocale(LC_ALL, "korean");
	_wsetlocale(LC_ALL, L"korean");
#endif
	
	std::string str = "테스트";
	std::wstring wstr = L"wcout 테스트";
	std::string str2;

	std::cout << str << std::endl;
	std::wcout << wstr << std::endl;
	wprintf(L"%s", wstr.c_str());

	aptoCore::Graphics::Initialize();

	if (!isResize)
	{
		aptoCore::Graphics::Resize(1920, 1080);
		isResize = !isResize;
	}

	while (aptoCore::Graphics::isRunEngine())
	{
		aptoCore::Graphics::Render(1.0f);
	}

	aptoCore::Graphics::Finalize();

	return 0;
}
