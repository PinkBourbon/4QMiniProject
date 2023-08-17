#pragma once
//#define YUNJINDLLEXPORT

#ifdef YUNJINDLLEXPORT
<<<<<<< HEAD
import aptoCore.Graphics;
#else
#include "../../YunGine/DXRenderer/IDX11Render.h"
#endif

#ifdef _DEBUG
#define RENDER_PATH L"..\\x64\\Debug\\DXRenderer.dll"
#else 
#define RENDER_PATH L"DXRenderer.dll"
#endif
=======
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
>>>>>>> pr/16
