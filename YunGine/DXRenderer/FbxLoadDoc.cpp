#include "FbxLoadDoc.h"
#include "Utility.h"

FbxLoadDoc::FbxLoadDoc()
{

}

FbxLoadDoc::~FbxLoadDoc()
{

}

void FbxLoadDoc::LoadFbx(FbxString filepath)
{
	FbxManager* manager = FbxManager::Create();
	FbxIOSettings* setting = FbxIOSettings::Create(manager,IOSROOT);
	FbxImporter* importer = FbxImporter::Create(manager, "");

	const char* filename = filepath;
	//wstostr(filepath,filename);

	bool importstatus = importer->Initialize(filename, -1, manager->GetIOSettings());

	FbxScene* scene = FbxScene::Create(manager, "scene");

	int FileMajor, FileMinor, FileRevision;

	importer->GetFileVersion();
}

void FbxLoadDoc::CheckFile()
{

}
