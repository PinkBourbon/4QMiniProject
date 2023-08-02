#include "Camera.h"

Camera::Camera()
	: _Position(0.0f, 0.0f, 0.0f),	// 카메라의 위치
	_Right(1.0f, 0.0f, 0.0f),		// 오른쪽으로 돌기 위한 변수
	_Up(0.0f, 1.0f, 0.0f),			// 왼쪽으로 돌기 위한 변수
	_Look(0.0f, 0.0f, 1.0f),		// 카메라가 보는 방향을 위한 변수
	_Aspect(),
	_FarWindowHeight(),
	_FarZ(),
	_FovY(),
	_NearWindowHeight(),
	_NearZ(),
	_Proj(),
	_View()
{

}

Camera::~Camera()
{

}

DirectX::XMFLOAT3 Camera::GetPosition() const
{
	return _Position;
}

DirectX::XMVECTOR Camera::GetPositionXM() const
{
	return DirectX::XMLoadFloat3(&_Position);
}

void Camera::SetPosition(float x, float y, float z)
{
	_Position = DirectX::XMFLOAT3(x, y, z);
}

void Camera::SetPosition(const DirectX::XMFLOAT3& v)
{
	_Position = v;
}

DirectX::XMVECTOR Camera::GetRightXM() const
{
	return DirectX::XMLoadFloat3(&_Right);
}

DirectX::XMFLOAT3 Camera::GetRight() const
{
	return _Right;
}

DirectX::XMVECTOR Camera::GetUpXM() const
{
	return DirectX::XMLoadFloat3(&_Up);
}

DirectX::XMFLOAT3 Camera::GetUp() const
{
	return _Up;
}

DirectX::XMVECTOR Camera::GetLookXM() const
{
	return DirectX::XMLoadFloat3(&_Look);
}

DirectX::XMFLOAT3 Camera::GetLook() const
{
	return _Look;
}

float Camera::GetNearZ() const
{
	return _NearZ;
}

float Camera::GetFarZ() const
{
	return _FarZ;
}

float Camera::GetAspect() const
{
	return _Aspect;
}

float Camera::GetFovY() const
{
	return _FovY;
}

float Camera::GetFovX() const
{
	#pragma warning(disable: 4244)
	float halfWidth = 0.5f * GetNearWindowWidth();
	return 2.0f * atan(halfWidth / _NearZ);
}

float Camera::GetNearWindowWidth() const
{
	return _Aspect * _NearWindowHeight;
}

float Camera::GetNearWindowHeight() const
{
	return _NearWindowHeight;
}

float Camera::GetFarWindowWidth() const
{
	return _Aspect * _FarWindowHeight;
}

float Camera::GetFarWindowHeight() const
{
	return _FarWindowHeight;
}

void Camera::SetLens(float fovY, float aspect, float zn, float zf)
{
	// cache properties
	_FovY = fovY;
	_Aspect = aspect;
	_NearZ = zn;
	_FarZ = zf;

	_NearWindowHeight = 2.0f * _NearZ * tanf(0.5f * _FovY);
	_FarWindowHeight = 2.0f * _FarZ * tanf(0.5f * _FovY);

	DirectX::XMMATRIX P = DirectX::XMMatrixPerspectiveFovLH(_FovY, _Aspect, _NearZ, _FarZ);
	XMStoreFloat4x4(&_Proj, P);
}

void Camera::LookAt(DirectX::FXMVECTOR pos, DirectX::FXMVECTOR target, DirectX::FXMVECTOR worldUp)
{
	// 시선벡터와 월드업을 외적하면 right벡터가 나오고
	// 다시 그 right벡터와 시선벡터를 외적하면 내 up벡터가 나옴
	DirectX::XMVECTOR L = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(target, pos));
	DirectX::XMVECTOR R = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(worldUp, L));
	DirectX::XMVECTOR U = DirectX::XMVector3Cross(L, R);

	DirectX::XMStoreFloat3(&_Position, pos);
	DirectX::XMStoreFloat3(&_Look, L);
	DirectX::XMStoreFloat3(&_Right, R);
	DirectX::XMStoreFloat3(&_Up, U);
}

void Camera::LookAt(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& target, const DirectX::XMFLOAT3& up)
{
	DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&pos);
	DirectX::XMVECTOR T = DirectX::XMLoadFloat3(&target);
	DirectX::XMVECTOR U = DirectX::XMLoadFloat3(&up);

	LookAt(P, T, U);
}

DirectX::XMMATRIX Camera::View() const
{
	return DirectX::XMLoadFloat4x4(&_View);
}

DirectX::XMMATRIX Camera::Proj() const
{
	return DirectX::XMLoadFloat4x4(&_Proj);
}

DirectX::XMMATRIX Camera::ViewProj() const
{
	return DirectX::XMLoadFloat4x4(&_Proj);
}

void Camera::Strafe(float d)
{
	// mPosition += d*mRight
	DirectX::XMVECTOR s = DirectX::XMVectorReplicate(d);
	DirectX::XMVECTOR r = DirectX::XMLoadFloat3(&_Right);
	DirectX::XMVECTOR p = DirectX::XMLoadFloat3(&_Position);
	DirectX::XMStoreFloat3(&_Position, DirectX::XMVectorMultiplyAdd(s, r, p));
}

void Camera::Walk(float d)
{
	// mPosition += d*mLook
	DirectX::XMVECTOR s = DirectX::XMVectorReplicate(d);
	DirectX::XMVECTOR l = DirectX::XMLoadFloat3(&_Look);
	DirectX::XMVECTOR p = DirectX::XMLoadFloat3(&_Position);
	DirectX::XMStoreFloat3(&_Position, DirectX::XMVectorMultiplyAdd(s, l, p));
}

void Camera::WorldUpDown(float d)
{
	// mPosition += d * mUp
	DirectX::XMVECTOR scale = DirectX::XMVectorReplicate(d);
	DirectX::XMVECTOR up = DirectX::XMLoadFloat3(&_Up);
	DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&_Position);
	DirectX::XMStoreFloat3(&_Position, DirectX::XMVectorMultiplyAdd(scale, up, position));
}

void Camera::Pitch(float angle)
{
	// Rotate up and look vector about the right vector.

	DirectX::XMMATRIX R = DirectX::XMMatrixRotationAxis(DirectX::XMLoadFloat3(&_Right), angle);

	DirectX::XMStoreFloat3(&_Up, XMVector3TransformNormal(XMLoadFloat3(&_Up), R));
	DirectX::XMStoreFloat3(&_Look, XMVector3TransformNormal(XMLoadFloat3(&_Look), R));
}

void Camera::RotateY(float angle)
{
	// Rotate the basis vectors about the world y-axis.

	DirectX::XMMATRIX R = DirectX::XMMatrixRotationY(angle);

	DirectX::XMStoreFloat3(&_Right, XMVector3TransformNormal(XMLoadFloat3(&_Right), R));
	DirectX::XMStoreFloat3(&_Up, XMVector3TransformNormal(XMLoadFloat3(&_Up), R));
	DirectX::XMStoreFloat3(&_Look, XMVector3TransformNormal(XMLoadFloat3(&_Look), R));

}

void Camera::UpdateViewMatrix()
{
	DirectX::XMVECTOR R = DirectX::XMLoadFloat3(&_Right);
	DirectX::XMVECTOR U = DirectX::XMLoadFloat3(&_Up);
	DirectX::XMVECTOR L = DirectX::XMLoadFloat3(&_Look);
	DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&_Position);

	// Keep camera's axes orthogonal to each other and of unit length.
	L = DirectX::XMVector3Normalize(L);
	U = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(L, R));

	// U, L already ortho-normal, so no need to normalize cross product.
	R = DirectX::XMVector3Cross(U, L);

	// Fill in the view matrix entries.
	float x = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, R));
	float y = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, U));
	float z = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, L));

	DirectX::XMStoreFloat3(&_Right, R);
	DirectX::XMStoreFloat3(&_Up, U);
	DirectX::XMStoreFloat3(&_Look, L);

	_View(0, 0) = _Right.x;
	_View(1, 0) = _Right.y;
	_View(2, 0) = _Right.z;
	_View(3, 0) = x;
	 
	_View(0, 1) = _Up.x;
	_View(1, 1) = _Up.y;
	_View(2, 1) = _Up.z;
	_View(3, 1) = y;
	 
	_View(0, 2) = _Look.x;
	_View(1, 2) = _Look.y;
	_View(2, 2) = _Look.z;
	_View(3, 2) = z;
	 
	_View(0, 3) = 0.0f;
	_View(1, 3) = 0.0f;
	_View(2, 3) = 0.0f;
	_View(3, 3) = 1.0f;
}
