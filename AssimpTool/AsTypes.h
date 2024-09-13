#pragma once
#include "VertexData.h"

using VertexType = VertexTextureNormalTangentBlendData;


struct asBone
{
	string name;
	int32 index = -1;
	int32 parent = -1;
	Matrix transform;
};

struct asMesh
{
	string name;
	aiMesh* mesh;
	vector<VertexType> vertices;
	vector<uint32> indices;

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

