module;
#include <DirectXMath.h>

module apto.math.Matrix4f;


namespace apto
{
	Matrix4f::operator DirectX::XMMATRIX() const noexcept
	{
		return DirectX::XMMATRIX
		{
			e[0][0], e[0][1], e[0][2], e[0][3],
			e[1][0], e[1][1], e[1][2], e[1][3],
			e[2][0], e[2][1], e[2][2], e[2][3],
			e[3][0], e[3][1], e[3][2], e[3][3],
		};
	}
}
