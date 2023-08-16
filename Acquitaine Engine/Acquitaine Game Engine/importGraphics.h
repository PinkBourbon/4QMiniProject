#pragma once
//#define YUNJINDLLEXPORT

#ifdef YUNJINDLLEXPORT
import aptoCore.Graphics;
#else
#include "../../YunGine/DXRenderer/IDX11Render.h"
#endif

#ifdef _DEBUG
#define RENDER_PATH L"..\\x64\\Debug\\DXRenderer.dll"
#else 
#define RENDER_PATH L"DXRenderer.dll"
#endif
