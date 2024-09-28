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

private:
	//물체를 가지고있는 추가 삭제 편하지만 순회에는 안좋다 검색활용
	unordered_set<shared_ptr<GameObject>> _objects;
	//카메라
	unordered_set<shared_ptr<GameObject>> _cameras;
	//빛
	unordered_set<shared_ptr<GameObject>> _lights;
};

