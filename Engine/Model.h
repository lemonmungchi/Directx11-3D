#pragma once

struct ModelBone;
struct ModelMesh;

class Model : public enable_shared_from_this<Model>
{
public:
	Model();
	~Model();

public:
	//custom -> Memory
	void ReadMaterial(wstring filename);
	void ReadModel(wstring filename);

	//헬퍼함수
	uint32 GetMaterialCount() { return static_cast<uint32>(_materials.size()); }
	vector<shared_ptr<Material>>& GetMaterials() { return _materials; }
	shared_ptr<Material> GetMaterialByIndex(uint32 index) { return _materials[index]; }
	shared_ptr<Material> GetMaterialByName(const wstring& name);

	uint32 GetMeshCount() { return static_cast<uint32>(_meshes.size()); }
	vector<shared_ptr<ModelMesh>>& GetMeshes() { return _meshes; }
	shared_ptr<ModelMesh> GetMeshByIndex(uint32 index) { return _meshes[index]; }
	shared_ptr<ModelMesh> GetMeshByName(const wstring& name);

	uint32 GetBoneCount() { return static_cast<uint32>(_bones.size()); }
	vector<shared_ptr<ModelBone>>& GetBones() { return _bones; }
	shared_ptr<ModelBone> GetBoneByIndex(uint32 index) { return (index < 0 || index >= _bones.size() ? nullptr : _bones[index]); }
	shared_ptr<ModelBone> GetBoneByName(const wstring& name);
private:
	//캐쉬정보 채워주기	
	void BindCacheInfo();

private:
	wstring _modelPath = L"../Resources/Models/";
	wstring _texturePath = L"../Resources/Textures/";

private:
	shared_ptr<ModelBone> _root;
	vector<shared_ptr<Material>> _materials;
	vector<shared_ptr<ModelBone>> _bones;
	vector<shared_ptr<ModelMesh>> _meshes;
};

