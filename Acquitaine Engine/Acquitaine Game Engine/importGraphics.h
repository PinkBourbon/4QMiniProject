#pragma once
#define YUNJINDLLEXPORT

#ifdef YUNJINDLLEXPORT
#pragma comment (lib, "DXRenderer.lib")
#include "../../YunGine/DXRenderer/IDX11Render.h"
#else
import aptoCore.Graphics;
#endif

#ifdef _DEBUG
#define RENDER_PATH L"..\\x64\\Debug\\DXRenderer.dll"
#else 
#define RENDER_PATH L"DXRenderer.dll"
#endif
