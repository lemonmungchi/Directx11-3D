#pragma once


class Scene
{
public:
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	
	//추가
	virtual void Add(shared_ptr<GameObject> object);
	//제거
	virtual void Remove(shared_ptr<GameObject> object);

	
	unordered_set<shared_ptr<GameObject>> GetObjects() { return _objects; }
	//일단 하나라고 가정하고 제일 처음꺼 가져오기
	shared_ptr<GameObject> GetCamera() { return _cameras.empty() ? nullptr : *_cameras.begin(); }
	shared_ptr<GameObject> GetLight() { return _lights.empty() ? nullptr : *_lights.begin(); }

	shared_ptr<class GameObject> Pick(int32 screenX, int32 screenY);

private:
	//물체를 가지고있는 추가 삭제 편하지만 순회에는 안좋다 검색활용
	unordered_set<shared_ptr<GameObject>> _objects;
	//카메라
	unordered_set<shared_ptr<GameObject>> _cameras;
	//빛
	unordered_set<shared_ptr<GameObject>> _lights;
};

