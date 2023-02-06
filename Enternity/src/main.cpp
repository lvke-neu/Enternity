#include "Engine/Math/Matrix4x4.h"

int main()
{

	//1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
	Enternity::Matrix4x4f mat4_1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };


	Enternity::Matrix4x4f mat4_2{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

	Enternity::Matrix4x4f mat4_3;
	mat4_3 = mat4_1 * mat4_2;

	Enternity::Matrix4x4f mat4_4;
	mat4_4 = Enternity::Matrix4x4f::Transpose(mat4_3);

	return 0;
}