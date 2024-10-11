#pragma once


class Scene
{
public:
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	
	virtual void Render();

	//추가
	virtual void Add(shared_ptr<GameObject> object);
	//제거
	virtual void Remove(shared_ptr<GameObject> object);

	
	unordered_set<shared_ptr<GameObject>>& GetObjects() { return _objects; }
	shared_ptr<GameObject> GetMainCamera();
	shared_ptr<GameObject> GetUICamera();
	shared_ptr<GameObject> GetLight() { return _lights.empty() ? nullptr : *_lights.begin(); }

	void PickUI();

	shared_ptr<class GameObject> Pick(int32 screenX, int32 screenY);

	void CheckCollision();

private:
	//물체를 가지고있는 추가 삭제 편하지만 순회에는 안좋다 검색활용
	unordered_set<shared_ptr<GameObject>> _objects;
	//카메라
	unordered_set<shared_ptr<GameObject>> _cameras;
	//빛
	unordered_set<shared_ptr<GameObject>> _lights;
};

