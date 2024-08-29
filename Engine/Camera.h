#pragma once
#include "Component.h"

enum class ProjectType
{
	Persperctive,		//원근투영
	Orthographic,		//직교투영
};

class Camera : public Component
{
	using Super = Component;
public:
	Camera();
	virtual ~Camera();

	virtual void Update() override;

	void UpdateMatrix();

	void SetNear(float value) { _near = value; }
	void SetFar(float value) { _far = value; }
	void SetFOV(float value) { _fov = value; }
	void SetWidth(float value) { _width = value; }
	void SetHeight(float value) { _height = value; }

	Matrix& GetViewMatrix() { return _matview; }
	Matrix& GetProjectionMatrix() { return _matProjection; }
	

private:
	Matrix _matview = Matrix::Identity;
	Matrix _matProjection = Matrix::Identity;

	float _near = 1.f;
	float _far = 1000.f;
	float _fov = XM_PI / 4.f;
	float _width = 0.f;
	float _height = 0.f;
public:
	//일단 카메라가 한개라고 가정
	static Matrix S_MatView;
	static Matrix S_MatProjection;
};

