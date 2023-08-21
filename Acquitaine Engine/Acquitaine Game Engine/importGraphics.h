#pragma once
#define YUNJINDLLEXPORT

#ifdef YUNJINDLLEXPORT
#pragma comment (lib, "DXRenderer.lib")
#include "../../YunGine/DXRenderer/IDX11Render.h"
#else
import aptoCore.Graphics;
using aptoCore::Graphics::Initialize;
using aptoCore::Graphics::Render;
using aptoCore::Graphics::Finalize;
using aptoCore::Graphics::RegisterObject;
using aptoCore::Graphics::DeregisterObject;
#endif
