module;
#include <cmath>
module apto.graphics.Camera;

import apto.math.Vector3f;

namespace apto
{
	void Camera::SetPosition(float x, float y, float z)
	{
		transform.SetPosition(x, y, z);
	}

	void Camera::AddPosition(float x, float y, float z)
	{
		transform.AddPosition(x, y, z);
	}

	void Camera::SetRotation(float x, float y, float z)
	{
		transform.SetRotation(x, y, z);
	}

	void Camera::AddRotationAxis(const Vector3f& axis, float radian)
	{
		transform.AddRotation(axis, radian);
	}

	void Camera::LookAt(float x, float y, float z)
	{
		transform.LookAt(Vector4f(x, y, z, 1.0f));
	}

	void Camera::SetPropeties(float viewportWidth, float viewportHeight, float fovDegree /*= 60.f*/, float nearZ /*= 0.1f*/, float farZ /*= 10000.f*/)
	{
		_viewportWidth = viewportWidth;
		_viewportHeight = viewportHeight;
		_fov = DegToRad(fovDegree);
		_nearZ = nearZ;
		_farZ = farZ;
	}

	void Camera::SetOrthographic()
	{
		_isOrtho = true;
	}

	void Camera::SetPerspective()
	{
		_isOrtho = false;
	}

	Matrix4f Camera::GetViewMatrix4f()
	{
		Matrix4f matrix = transform.GetMatrix4f();
		Vector4f u = Vector4f(1.0f, 0.0f, 0.0f, 0.0f) * matrix;
		Vector4f v = Vector4f(0.0f, 1.0f, 0.0f, 0.0f) * matrix;
		Vector4f n = Vector4f(0.0f, 0.0f, 1.0f, 0.0f) * matrix;
		Vector4f& eye = transform._position;

		return Matrix4f
		{
			u.x,				v.x,				n.x,				0.0f,
			u.y,				v.y,				n.y,				0.0f,
			u.z,				v.z,				n.z,				0.0f,
			-eye.Vector3Dot(u), -eye.Vector3Dot(v), -eye.Vector3Dot(n), 1.0f
		};
	}

	Matrix4f Camera::GetProjectionMatrix4f()
	{
		if (_isOrtho)
		{
			float fRange = 1.0f / (_farZ - _nearZ);

			return Matrix4f
			{
				2.0f / _viewportWidth,	0.0f,						0.0f,				0.0f,
				0.0f,					2.0f / _viewportHeight,		0.0f,				0.0f,
				0.0f,					0.0f,						fRange,				0.0f,
				0.0f,					0.0f,						-fRange * _nearZ,	1.0f
			};
		}
		else
		{
			float d = cos(_fov / 2) / sin(_fov / 2);
			float a = _viewportWidth / _viewportHeight;
			float divide = _farZ / (_farZ - _nearZ);

			return Matrix4f
			{
				d / a,	0.0f,	0.0f,				0.0f,
				0.0f,	d,		0.0f,				0.0f,
				0.0f,	0.0f,	divide,				1.0f,
				0.0f,	0.0f,	-divide * _nearZ,	0.0f
			};
		}
	}
}