#pragma once

using VetexType = VertexTextureNormalTangentBlendData;


struct asBone
{

};

struct asMesh
{
	string name;
	aiMesh* mesh;
	vector<VetexType> vertices;
	vector<uint32> indicies;

	int32 boneIndex;		//계층구조
	string materialName;
};

struct asMaterial
{
	string name;
	Color ambient;
	Color diffuse;
	Color specular;
	Color emissive;
	string diffuseFile;
	string specularFile;
	string normalFile;
};

