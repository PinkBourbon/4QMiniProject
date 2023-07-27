module;
#include <cmath>

module apto.math.Quaternion;


namespace apto
{
	void Quaternion::SetEuler(float degreeX, float degreeY, float degreeZ) noexcept
	{
		float radX = DegToRad(degreeX * 0.5f);
		float radY = DegToRad(degreeY * 0.5f);
		float radZ = DegToRad(degreeZ * 0.5f);

		//// �ϴ� YXZ ������ ����
		float cosR = cosf(radZ);
		float sinR = sinf(radZ);
		float cosY = cosf(radY);
		float sinY = sinf(radY);
		float cosP = cosf(radX);
		float sinP = sinf(radX);

		w = cosR * cosP * cosY + sinR * sinP * sinY;
		x = cosR * sinP * cosY + sinR * cosP * sinY;
		y = cosR * cosP * sinY - sinR * sinP * cosY;
		z = sinR * cosP * cosY - cosR * sinP * sinY;

		Normalize();
	}

	void Quaternion::SetEuler(const Vector3f& euler) noexcept
	{
		SetEuler(euler.x, euler.y, euler.z);
	}

	Vector3f Quaternion::GetEuler() const noexcept
	{
		// �ϴ� YXZ ������ ����
		float sRcP = 2.0f * (w * z + x * y);  // sinRoll * cosPitch
		float cRcP = 1.0f - 2.0f * (z * z + x * x); // cosRoll * cosPitch
		float roll = atan2(sRcP, cRcP);

		float sP = 2.0f * (w * x - y * z); // sinPitch
		float pitch = 0.0f;

		// ��ũ ���� �Լ��� ���ǿ��� -1 ~ 1�̹Ƿ�, �̸� ����� ��츦 ó������� �Ѵ�.
		if (sP < -1.0f)
		{
			pitch = -PI<float> / 2.0f;
		}
		else if (sP > 1.0f)
		{
			pitch = PI<float> / 2.0f;
		}
		else
		{
			pitch = asinf(sP);
		}

		float sYcP = 2.0f * (w * y + x * z); // sinYaw * cosPitch
		float cYcP = 1.0f - 2.0f * (x * x + y * y); // cosYaw * cosPitch
		float yaw = atan2(sYcP, cYcP);

		return Vector3f(RadToDeg(pitch), RadToDeg(yaw), RadToDeg(roll));
	}
}