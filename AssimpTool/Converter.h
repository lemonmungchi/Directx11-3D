#pragma once
class Converter
{
public:
	Converter();
	~Converter();

public:
	void ReadAssetFile(wstring  file);


private:
	wstring _assetPath = L"../Resources/Assets/";
	wstring _modelPath = L"../Resources/Models/";
	wstring _texturePath = L"../Resources/Texture/";

private:
	shared_ptr<Assimp::Importer> _importer;
	const aiScene* _scene;				//로드했을 때 제일 상위계층
};

