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

//Animation

//Skinning
struct asBlendWeight
{
	//뼈 목록
	Vec4 indices = Vec4(0, 0, 0, 0);
	Vec4 weights = Vec4(0, 0, 0, 0);

	void Set(uint32 index, uint32 boneIndex, float weight)
	{
		float i = (float)boneIndex;
		float w = weight;

		switch (index)
		{
		case 0: indices.x = i; weights.x = w; break;
		case 1: indices.y = i; weights.y = w; break;
		case 2: indices.z = i; weights.z = w; break;
		case 3: indices.w = i; weights.w = w; break;
		}
	}
};

//영향을 주는 각 뼈들 - 정점마다 - (뼈번호, 가중치)
struct asBoneWeights
{
	void AddWeights(uint32 boneIndex, float weight)
	{
		if (weight <= 0.0f)
			return;
		
		//weight 값이 나보다 작은애가 있는지 찾는다.-> 위치찾기
		auto findIt = std::find_if(boneWeights.begin(), boneWeights.end(),
			[weight](const Pair& p) {return weight > p.second; });

		//그 위치앞에 추가
		boneWeights.insert(findIt, Pair(boneIndex, weight));
	}

	//4개의 뼈 / 가중치 목록 채워주기
	asBlendWeight GetBlendWeight()
	{
		asBlendWeight blendWeights;

		for (uint32 i = 0; i < boneWeights.size(); i++)
		{
			if (i >= 4)
				break;

			//가중치설정
			blendWeights.Set(i, boneWeights[i].first, boneWeights[i].second);
		}

		return blendWeights;
	}

	// 정규화 합 1로 맞춰주기 
	void Normalize()
	{
		if (boneWeights.size() >= 4)
			boneWeights.resize(4);

		float totalWeight = 0.f;
		for (const auto& item : boneWeights)
			totalWeight += item.second;

		float scale = 1.f / totalWeight;
		for (auto& item : boneWeights)
			item.second *= scale;
	}

	using Pair = pair<int32, float>;
	vector<Pair> boneWeights;

};

//Animation Clip

struct asKeyframeData
{
	float time; 
	//SRT
	Vec3 scale;
	Quaternion rotation;
	Vec3 translation;
};

//한프레임
struct asKeyframe
{
	string boneName;
	vector<asKeyframeData> transforms;
};


struct asAnimation
{
	string name;
	uint32 frameCount;		//몇프레임짜리
	float frameRate;
	float duration;
	vector<shared_ptr<asKeyframe>> keyframes;
};

//캐시용
struct asAnimationNode
{
	aiString name;
	vector<asKeyframeData> keyframe;
};

