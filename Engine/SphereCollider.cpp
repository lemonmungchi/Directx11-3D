#include "pch.h"
#include "SphereCollider.h"

SphereCollider::SphereCollider()
	: BaseCollider(ColliderType::Sphere)
{

}

SphereCollider::~SphereCollider()
{

}

void SphereCollider::Update()
{
	_boundingSphere.Center = GetGameObject()->GetTransform()->GetPosition();

	Vec3 scale = GetGameObject()->GetTransform()->GetScale();
	//스캐일중에 제일큰애따라서 반지름 증가하도록
	_boundingSphere.Radius = _radius * max(max(scale.x, scale.y), scale.z);
}

bool SphereCollider::Intersects(Ray& ray, OUT float& distance)
{
	return _boundingSphere.Intersects(ray.position, ray.direction, OUT distance);
}