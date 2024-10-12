#pragma once
#include "Component.h"

struct VertexBillboard
{
	Vec3 position;
	Vec2 uv;
	Vec2 scale;
};

//정점 최대개수
#define MAX_BILLBOARD_COUNT 500

class Billboard : public Component
{
	using Super = Component;

public:
	Billboard();
	~Billboard();

	void Update();
	//만들어줄 위치
	void Add(Vec3 position, Vec2 scale);

	void SetMaterial(shared_ptr<Material> material) { _material = material; }
	void SetPass(uint8 pass) { _pass = pass; }

private:
	vector<VertexBillboard> _vertices;
	vector<uint32> _indices;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	//그려줄 애들의 수
	int32 _drawCount = 0;
	//그려준 애들의 수 - 바뀔때만 갱신
	int32 _prevCount = 0;

	shared_ptr<Material> _material;
	uint8 _pass = 0;
};

