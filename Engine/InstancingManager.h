#pragma once
#include "InstancingBuffer.h"

class GameObject;


class InstancingManager
{
	DECLARE_SINGLE(InstancingManager);

public:
	void Render(vector<shared_ptr<GameObject>>& gameObjects);
	void Clear() { _buffers.clear(); }
	void ClearData();

private:
	void RenderMeshRenderer(vector<shared_ptr<GameObject>>& gameObjects);

private:
	void AddData(InstanceID instanceId, InstancingData& data);

private:
	//짝 만들어주기
	map<InstanceID/*instanceId*/, shared_ptr<InstancingBuffer>> _buffers;
};



