#include "pch.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(ComponentType type)
	:_type(type)
{
}

Component::~Component()
{
}


std::shared_ptr<GameObject> Component::GetGameObject()
{
	return _cat.lock();
}

std::shared_ptr<Transform> Component::GetTransform()
{
	return _cat.lock()->GetTransform();
}


