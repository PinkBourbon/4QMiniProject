#pragma once
//#define YUNJINDLLEXPORT

#ifdef YUNJINDLLEXPORT
#include "../../YunGine/DXRenderer/IDX11Render.h"
#else
import aptoCore.Graphics;
#pragma comment (lib, "DXRenderer.lib")
#endif

// #ifdef _DEBUG
// #define RENDER_PATH L"..\\lib\\DXRenderer.dll"
// #else 
// #define RENDER_PATH L"DXRenderer.dll"
// #endif
