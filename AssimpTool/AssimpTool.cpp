#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{

	{
		shared_ptr<Converter> converter = make_shared<Converter>();

		// FBX -> Memory
		converter->ReadAssetFile(L"House/House.fbx");

		//Memory -> CustomData

		//CustomData -> Memory
	}
}

void AssimpTool::Update()
{

}

void AssimpTool::Render()
{

}
