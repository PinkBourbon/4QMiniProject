#pragma once
#include <vector>
#include <windows.h>

#include <iostream>
#include <string>
#include <locale>

#include <fbxsdk.h>
#include "Vertex.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Lib\\debug\\libfbxsdk-md.lib")
#pragma comment(lib, "..\\Lib\\debug\\libxml2-md")
#pragma comment(lib, "..\\Lib\\debug\\zlib-md")
#else
#pragma comment(lib, "..\\Lib\\release\\libfbxsdk-md.lib")
#pragma comment(lib, "..\\Lib\\release\\libxml2-md")
#pragma comment(lib, "..\\Lib\\release\\zlib-md")
#endif 

// 전역 함수로 만들어서 사용
HRESULT LoadFbx2(std::vector<Vertex3>* pOutVertexVector, const char* fileroot);