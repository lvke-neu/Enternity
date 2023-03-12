#include "Application/Application.h"


#include "Core/Math/Vector.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Math.h"
void Test()
{
	using namespace Enternity;
	Vector2d vec1(1, 2);
	Vector2d vec2(3, 4);

	//auto res = Vector2DotProduct(vec1, vec2);
	//Matrix4x4f mat1{1,2,3,4,4,4,4,4,4,4,4,4, 4,4,4,4 };
	//Matrix4x4f mat2{1,2,3,4,5,6,7,4,4,4,4,4, 4,4,4,4 };
	//
	//mat1 += mat1;
	Matrix4x4f scaleMatrxi;
	Matrix4x4Scale(scaleMatrxi, 1.0f, 2.0f, 3.0f);
	Matrix4x4f translateMatrxi;
	Matrix4x4Translate(translateMatrxi, 1.0f, 2.0f, 3.0f);
	Matrix4x4f rotateMatrix;
	Matrix4x4RotateYawPitchRoll(rotateMatrix, 30.0f, 60.f, 0.0f, false);

	Matrix4x4f perspectiveMatrix;
	Matrix4x4Perspective(perspectiveMatrix, 45.0f, 2.0f, 0.1f, 100.0f, false);

	int i = 0;
	i++;
}

int main(int argc, const char** argv) {

	Test();

	Enternity::Application app;

	app.Initialize(1200, 800, "hahaha");
	app.Run();
	app.Finalize();
	
	return 0;
}


