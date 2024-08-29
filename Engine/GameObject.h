#pragma once
#include "Component.h"

class MonoBehaviour;
class Transform;
class Camera;
class MeshRenderer;
class Animator;

class GameObject : public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	~GameObject();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();

	//헬퍼함수
	shared_ptr<Component> GetFixedComponent(ComponentType type);
	shared_ptr<Transform> GetTransform();
	shared_ptr<Camera> GetCamera();
	//shared_ptr<MeshRenderer> GetMeshRenderer();
	//shared_ptr<Animator> GetAnimator();

	shared_ptr<Transform> GetOrAddTransform();
	void AddComponent(shared_ptr<Component> component);

protected:
	//개수가 고정인 
	std::array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
	//개수가 동적인
	vector<shared_ptr<MonoBehaviour>> _scripts;
};

