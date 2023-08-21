#include <iostream>
#include "Vertex.h"
#include "AptoMacro.h"
#include <memory>

import apto.math;
import apto.util.Time;
//import apto.graphics.Camera;
import aptoCore.Graphics;
import aptoCore.rawData;

import apto;

bool g_isResized = false;

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

	aptoCore::RawNode node(L"raw Data");
	node.mesh.reset(new aptoCore::RawMesh());
	std::wcout << node.mesh->indices.size() << std::endl;

	aptoCore::Graphics::Initialize();

	apto::Transform tr;

	std::wcout << tr.GetPosition().x << std::endl;

	if (!g_isResized)
	{
		g_isResized = aptoCore::Graphics::Resize(1920, 1080);
	}

	while (aptoCore::Graphics::isRunEngine())
	{
		aptoCore::Graphics::Render(1.0f);
	}

	aptoCore::Graphics::Finalize();

	return 0;
}
