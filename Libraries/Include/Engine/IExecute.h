#pragma once

class IExecute
{
//실행단위
public:
	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render() abstract;
};

