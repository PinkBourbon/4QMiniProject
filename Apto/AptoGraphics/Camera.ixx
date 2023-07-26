export module apto.graphics.Camera;

import apto.math.Matrix4f;
import apto.math.Common;
import apto.Transform;

export namespace apto
{
	struct Vector3f;
}

export namespace apto
{
	class __declspec(dllexport) Camera
	{
	public:
		Camera(float viewportWidth = 32.f, float viewportHeight = 18.f, float fovDegree = 60.f, float nearZ = 0.1f, float farZ = 10000.f) :
			transform(),
			_fov(DegToRad(fovDegree)),
			_viewportWidth(viewportWidth),
			_viewportHeight(viewportHeight),
			_nearZ(nearZ),
			_farZ(farZ),
			_isOrtho(false) {}
		~Camera() = default;
		void SetPosition(float x, float y, float z);
		void AddPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void AddRotationAxis(const Vector3f& axis, float radian);
		void LookAt(float x, float y, float z);
		void SetPropeties(float viewportWidth, float viewportHeight, float fovDegree = 60.f, float nearZ = 0.1f, float farZ = 10000.f);

		void SetOrthographic();
		void SetPerspective();

		Matrix4f GetViewMatrix4f();
		Matrix4f GetProjectionMatrix4f();

	public:
		Transform transform;

	private:
		float _fov;
		float _viewportWidth;
		float _viewportHeight;
		float _nearZ;
		float _farZ;

		bool _isOrtho;
	};
}