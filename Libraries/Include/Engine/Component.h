#pragma once

class GameObject;
class Transform;

enum class ComponentType : uint8
{
	Transform,
	MeshRenderer,
	ModelRenderer,
	Camera,
	Animator,
	Light,
	Collider,
	Terrain,
	Button,
	BillBoard,
	SnowBillBoard,
	// ...
	Script,

	End,
};

enum
{
	//개수가 고정인 컴포넌트 개수
	FIXED_COMPONENT_COUNT = static_cast<uint8>(ComponentType::End)-1
};

class Component
{
public:
	Component(ComponentType type);
	virtual ~Component();

	//생성될때 호출
	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void LateUpdate(){}
	virtual void FixedUpdate(){}

public:
	ComponentType GetType() { return _type; }

	shared_ptr<GameObject> GetGameObject();
	shared_ptr<Transform> GetTransform();

private:
	friend class GameObject;
	void SetGameObject(shared_ptr<GameObject> gameObject) { _gameObject = gameObject; }


protected:
	ComponentType _type;
	weak_ptr<GameObject> _gameObject;
};

