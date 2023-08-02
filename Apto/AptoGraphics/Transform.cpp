module;
#include <DirectXMath.h>
#include <cmath>
module apto.Transform;

import apto.math.Common;

namespace apto
{
	void Transform::SetMatrix(Matrix4f worldMatrix)
	{
		//DirectX::XMMatrixDecompose(&_scale.m, &_rotation.m, &_position.m, worldMatrix);

		//// 우선 바로 알 수 있는 x, y, z 위치를 뽑아낸다.
		//_position.x = worldMatrix.e[3][0];
		//_position.y = worldMatrix.e[3][1];
		//_position.z = worldMatrix.e[3][2];

		//// scale을 뽑아낸다.
		//Vector3f scaleXvec(worldMatrix.e[0][0], worldMatrix.e[0][1], worldMatrix.e[0][2]);
		//Vector3f scaleYvec(worldMatrix.e[1][0], worldMatrix.e[1][1], worldMatrix.e[1][2]);
		//Vector3f scaleZvec(worldMatrix.e[2][0], worldMatrix.e[2][1], worldMatrix.e[2][2]);

		//_scale.x = scaleXvec.Norm();
		//_scale.y = scaleYvec.Norm();
		//_scale.z = scaleZvec.Norm();

		//if (_scale.x == 0.0f || _scale.y == 0.0f || _scale.z == 0.0f)
		//{
		//	// 스케일 중 하나라도 0일 경우에 rotation을 뽑아낼 수 없다.
		//	// 따라서 회전하지 않은 상태로 만들고 그냥 리턴하자.
		//	_rotation.w = 1.0f;
		//	_rotation.x = 0.0f;
		//	_rotation.y = 0.0f;
		//	_rotation.z = 0.0f;
		//	return;
		//}

		//// scale 적용 전의 matrix를 만든다.
		//worldMatrix.v[0] /= _scale.x;
		//worldMatrix.v[1] /= _scale.y;
		//worldMatrix.v[2] /= _scale.z;

		//// 행렬식의 값이 0보다 작을 경우에 x, y, z 중 홀수 갯수의 축이 네거티브 스케일이기 때문에
		//// 임의의 하나의 축을 반전시켜서 짝수개 축을 네거티브 스케일로 만들어 회전행렬을 만들어낼 수 있도록 한다.
		//float det = worldMatrix.Determinant();
		//if (det < 0.0f)
		//{
		//	_scale.x = -_scale.x;
		//	worldMatrix.v[0] *= -1.0f;
		//}

		//// rotation을 뽑아낸다.
		//_rotation.w = sqrtf(1.0f + worldMatrix.e[0][0] + worldMatrix.e[1][1] + worldMatrix.e[2][2]) / 2.0f;

		//float w4 = (4.0f * _rotation.w);
		//_rotation.x = (worldMatrix.e[1][2] - worldMatrix.e[2][1]) / w4;
		//_rotation.y = (worldMatrix.e[2][0] - worldMatrix.e[0][2]) / w4;
		//_rotation.z = (worldMatrix.e[0][1] - worldMatrix.e[1][0]) / w4;

		//_rotation.Normalize();

		/*
			static const XMVECTOR* pvCanonicalBasis[3] = {
		&g_XMIdentityR0.v,
		&g_XMIdentityR1.v,
		&g_XMIdentityR2.v
	};

	assert(outScale != nullptr);
	assert(outRotQuat != nullptr);
	assert(outTrans != nullptr);

	// Get the translation
	outTrans[0] = M.r[3];

	XMVECTOR* ppvBasis[3];
	XMMATRIX matTemp;
	ppvBasis[0] = &matTemp.r[0];
	ppvBasis[1] = &matTemp.r[1];
	ppvBasis[2] = &matTemp.r[2];

	matTemp.r[0] = M.r[0];
	matTemp.r[1] = M.r[1];
	matTemp.r[2] = M.r[2];
	matTemp.r[3] = g_XMIdentityR3.v;

	auto pfScales = reinterpret_cast<float*>(outScale);

	size_t a, b, c;
	XMVectorGetXPtr(&pfScales[0], XMVector3Length(ppvBasis[0][0]));
	XMVectorGetXPtr(&pfScales[1], XMVector3Length(ppvBasis[1][0]));
	XMVectorGetXPtr(&pfScales[2], XMVector3Length(ppvBasis[2][0]));
	pfScales[3] = 0.f;

	XM3RANKDECOMPOSE(a, b, c, pfScales[0], pfScales[1], pfScales[2])

		if (pfScales[a] < XM3_DECOMP_EPSILON)
		{
			ppvBasis[a][0] = pvCanonicalBasis[a][0];
		}
	ppvBasis[a][0] = XMVector3Normalize(ppvBasis[a][0]);

	if (pfScales[b] < XM3_DECOMP_EPSILON)
	{
		size_t aa, bb, cc;
		float fAbsX, fAbsY, fAbsZ;

		fAbsX = fabsf(XMVectorGetX(ppvBasis[a][0]));
		fAbsY = fabsf(XMVectorGetY(ppvBasis[a][0]));
		fAbsZ = fabsf(XMVectorGetZ(ppvBasis[a][0]));

		XM3RANKDECOMPOSE(aa, bb, cc, fAbsX, fAbsY, fAbsZ)

			ppvBasis[b][0] = XMVector3Cross(ppvBasis[a][0], pvCanonicalBasis[cc][0]);
	}

	ppvBasis[b][0] = XMVector3Normalize(ppvBasis[b][0]);

	if (pfScales[c] < XM3_DECOMP_EPSILON)
	{
		ppvBasis[c][0] = XMVector3Cross(ppvBasis[a][0], ppvBasis[b][0]);
	}

	ppvBasis[c][0] = XMVector3Normalize(ppvBasis[c][0]);

	float fDet = XMVectorGetX(XMMatrixDeterminant(matTemp));

	// use Kramer's rule to check for handedness of coordinate system
	if (fDet < 0.0f)
	{
		// switch coordinate system by negating the scale and inverting the basis vector on the x-axis
		pfScales[a] = -pfScales[a];
		ppvBasis[a][0] = XMVectorNegate(ppvBasis[a][0]);

		fDet = -fDet;
	}

	fDet -= 1.0f;
	fDet *= fDet;

	if (XM3_DECOMP_EPSILON < fDet)
	{
		// Non-SRT matrix encountered
		return false;
	}

	// generate the quaternion from the matrix
	outRotQuat[0] = XMQuaternionRotationMatrix(matTemp);
	return true;
		*/
	}

	void Transform::SetPosition(float x, float y, float z)
	{
		_position.x = x;
		_position.y = y;
		_position.z = z;
	}

	void Transform::SetPosition(const Vector4f& position)
	{
		_position = position;
	}

	void Transform::SetRotation(float degreeX, float degreeY, float degreeZ)
	{
		_rotation.SetEuler(degreeX, degreeY, degreeZ);
	}

	void Transform::SetRotation(const Vector3f& axis, float radian)
	{
		Quaternion q(axis, radian);
		_rotation = q;
		_rotation.Normalize();
	}

	void Transform::SetRotation(const Quaternion& q)
	{
		_rotation = q;
	}

	void Transform::SetScale(float x, float y, float z)
	{
		_scale.x = x;
		_scale.y = y;
		_scale.z = z;
	}

	void Transform::SetScale(const Vector4f& scale)
	{
		_scale = scale;
	}

	void Transform::AddPosition(float x, float y, float z)
	{
		_position.x += x;
		_position.y += y;
		_position.z += z;
	}

	void Transform::AddPosition(const Vector4f& position)
	{
		_position += position;
		_position.w = 1.0f;
	}

	void Transform::AddRotation(const Vector3f& axis, float radian)
	{
		//Quaternion q0{ DirectX::XMQuaternionRotationAxis(Vector4f{ axis, 0.0f }, radian) };
		Quaternion q(axis, radian);
		//q.SetEuler(degreeX, degreeY, degree);
		AddRotation(q);
	}

	void Transform::AddRotation(const Quaternion& q)
	{
		_rotation = q * _rotation;
		_rotation.Normalize();
	}

	void Transform::AddScale(float x, float y, float z)
	{
		_scale.x += x;
		_scale.y += y;
		_scale.z += z;
	}

	Matrix4f Transform::GetTransformMatrix4f() const
	{
		return Matrix4f
		{
			1.0f,			0.0f,			0.0f,			0.0f,
			0.0f,			1.0f,			0.0f,			0.0f,
			0.0f,			0.0f,			1.0f,			0.0f,
			_position.x,	_position.y,	_position.z,	1.0f
		};
	}

	Matrix4f Transform::GetRotationMatrix4f() const
	{
		float x2 = _rotation.x * _rotation.x;
		float y2 = _rotation.y * _rotation.y;
		float z2 = _rotation.z * _rotation.z;
		float xy = _rotation.x * _rotation.y;
		float xz = _rotation.x * _rotation.z;
		float yz = _rotation.y * _rotation.z;
		float wx = _rotation.w * _rotation.x;
		float wy = _rotation.w * _rotation.y;
		float wz = _rotation.w * _rotation.z;

		return Matrix4f
		{
			1.f - 2.f * (y2 + z2),	2.f * (xy + wz),		2.f * (xz - wy),		0.f,
			2.f * (xy - wz),		1.f - 2.f * (x2 + z2),	2.f * (yz + wx),		0.f,
			2.f * (xz + wy),		2.f * (yz - wx),		1.f - 2.f * (x2 + y2),	0.f,
			0.f,					0.f,					0.f,					1.f
		};
	}

	Matrix4f Transform::GetScaleMatrix4f() const
	{
		return Matrix4f
		{
			_scale.x,	0.0f,		0.0f,		0.0f,
			0.0f,		_scale.y,	0.0f,		0.0f,
			0.0f,		0.0f,		_scale.z,	0.0f,
			0.0f,		0.0f,		0.0f,		1.0f
		};
	}

	Matrix4f Transform::GetMatrix4f() const
	{
		return GetScaleMatrix4f() * GetRotationMatrix4f() * GetTransformMatrix4f();
	}

	void Transform::LookAt(Vector4f target)
	{
		// target을 바라보도록 회전
		Vector4f wantLook = target - _position;
		wantLook.Vector3Normalize();
		Vector4f currLook = Vector4f(0.f, 0.f, 1.f, 1.f) * GetMatrix4f() - _position;
		currLook.Vector3Normalize();
		Vector4f axis = currLook.Vector3Cross(wantLook);

		axis.Vector3Normalize();

		float test = wantLook.Vector3Dot(currLook);

		float angle = 0.0f;

		// 아크 코사인의 정의역이 -1 ~ 1이므로 그 이상일 경우 가장 가까운 각으로 보정해 준다.
		// 단, 1이아닌 0.99999같은 값으로 설정했을 경우에 연속으로 LookAt을 호출할 경우 오차가 누적되어 떨림 증상이 발생한다.
		if (test > 1.f)
		{
			angle = 0.0f;
		}
		else if (test < -1.f)
		{
			angle = PI<float>;
		}
		else
		{
			angle = acos(test);
		}

		Quaternion q{ axis, angle };

		_rotation = q * _rotation;
		_rotation.Normalize();
	}
}