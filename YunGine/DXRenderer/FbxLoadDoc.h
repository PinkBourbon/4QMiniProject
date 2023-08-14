#pragma once

#include <windows.h>
#include <fbxsdk.h>

class FbxLoadDoc
{
public:
	FbxLoadDoc();
	~FbxLoadDoc();

	void LoadFbx(FbxString filepath);

	void CheckFile();
};

