#include "pch.h"
#include "Camera.h"

Matrix Camera::S_MatView = Matrix::Identity;
Matrix Camera::S_MatProjection = Matrix::Identity;

Camera::Camera() : Super(ComponentType::Camera)
{
	_width = static_cast<float>(GAME->GetGameDesc().width);
	_height = static_cast<float>(GAME->GetGameDesc().height);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	UpdateMatrix();

	RENDER->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);
}

void Camera::UpdateMatrix()
{
	//카메라좌표
	Vec3 eyePosition = GetTransform()->GetPosition();
	//바라보는 방향
	Vec3 focusPosition = eyePosition + GetTransform()->GetLook(); 
	//위쪽방향 - 임의로 정해줘도 된다.
	Vec3 upDirection = GetTransform()->GetUp();
	//카메라 변환행렬 계산 - 월드의 역행렬
	S_MatView = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);

	//월드의 역행렬
	//S_MatView = GetTransform()->GetWorldMatrix().Invert();
	
	//필드오브 뷰,비율,니어,파
	S_MatProjection = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
}
