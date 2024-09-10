#include "pch.h"
#include "Converter.h"
#include "filesystem"
#include "Utils.h"

Converter::Converter()
{
	_importer = make_shared<Assimp::Importer>();
}

Converter::~Converter()
{
	 
}

void Converter::ReadAssetFile(wstring file)
{
	wstring fileStr = _assetPath + file;

	//파일가져오기
	auto p = std::filesystem::path(fileStr);
	assert(std::filesystem::exists(p));

	_scene = _importer->ReadFile(
		Utils::ToString(fileStr),
		aiProcess_ConvertToLeftHanded |
		aiProcess_Triangulate |			//삼각형 단위만 파싱
		aiProcess_GenUVCoords |			//uv좌표 생성
		aiProcess_GenNormals |			//노멀 매핑
		aiProcess_CalcTangentSpace
	);


	assert(_scene != nullptr);
}
