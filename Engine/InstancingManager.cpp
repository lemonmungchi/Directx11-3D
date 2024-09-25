#include "pch.h"
#include "InstancingManager.h"
#include "InstancingBuffer.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "ModelRenderer.h"
#include "ModelAnimator.h"
#include "Transform.h"
#include "Camera.h"

void InstancingManager::Render(vector<shared_ptr<GameObject>>& gameObjects)
{
	ClearData();

	RenderMeshRenderer(gameObjects);
	RenderModelRenderer(gameObjects);
}

void InstancingManager::RenderMeshRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
	//임시용- 물체걸러주기
	map<InstanceID, vector<shared_ptr<GameObject>>> cache;

	//분류
	for (shared_ptr<GameObject>& gameObject : gameObjects)
	{
		if (gameObject->GetMeshRenderer() == nullptr)
			continue;

		const InstanceID instanceId = gameObject->GetMeshRenderer()->GetInstanceID();
		cache[instanceId].push_back(gameObject);
	}

	//같은애들 모아서 그려주기
	for (auto& pair : cache)
	{
		const vector<shared_ptr<GameObject>>& vec = pair.second;

		//if (vec.size() == 1)
		//{
		//	vec[0]->GetMeshRenderer()->RenderSingle();
		//}
		//else
		{
			const InstanceID instanceId = pair.first;

			for (int32 i = 0; i < vec.size(); i++)
			{
				const shared_ptr<GameObject>& gameObject = vec[i];
				InstancingData data;
				data.world = gameObject->GetTransform()->GetWorldMatrix();

				AddData(instanceId, data);
			}

			//그려주기- 대표로 그려주기
			shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
			vec[0]->GetMeshRenderer()->RenderInstancing(buffer);
		}
	}
}

void InstancingManager::RenderModelRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
	map<InstanceID, vector<shared_ptr<GameObject>>> cache;

	for (shared_ptr<GameObject>& gameObject : gameObjects)
	{
		if (gameObject->GetModelRenderer() == nullptr)
			continue;

		const InstanceID instanceId = gameObject->GetModelRenderer()->GetInstanceID();
		cache[instanceId].push_back(gameObject);
	}

	for (auto& pair : cache)
	{
		const vector<shared_ptr<GameObject>>& vec = pair.second;

		//if (vec.size() == 1)
		//{
		//	vec[0]->GetMeshRenderer()->RenderSingle();
		//}
		//else
		{
			const InstanceID instanceId = pair.first;

			for (int32 i = 0; i < vec.size(); i++)
			{
				const shared_ptr<GameObject>& gameObject = vec[i];
				InstancingData data;
				data.world = gameObject->GetTransform()->GetWorldMatrix();

				AddData(instanceId, data);
			}

			shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
			vec[0]->GetModelRenderer()->RenderInstancing(buffer);
		}
	}
}


void InstancingManager::AddData(InstanceID instanceId, InstancingData& data)
{
	//인스턴스 아이디가 있는지 이미 로드했던게 아니라면
	if (_buffers.find(instanceId) == _buffers.end())
		_buffers[instanceId] = make_shared<InstancingBuffer>();

	_buffers[instanceId]->AddData(data);
}

void InstancingManager::ClearData()
{
	for (auto& pair : _buffers)
	{
		shared_ptr<InstancingBuffer>& buffer = pair.second;
		buffer->ClearData();
	}
}