#include "Matrix4x4.h"

namespace Enternity
{
	Matrix4x4f Matrix4x4f::IDENTITY =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	Matrix4x4f Matrix4x4f::ZERO =
	{
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	};

	Matrix4x4f::Matrix4x4f()
	{
		
	}

	Matrix4x4f::Matrix4x4f(
		float m00, float m01, float m02, float m03, 
		float m10, float m11, float m12, float m13, 
		float m20, float m21, float m22, float m23, 
		float m30, float m31, float m32, float m33)
	{
		mat4x4f[0][0] = m00; mat4x4f[0][1] = m01; mat4x4f[0][2] = m02; mat4x4f[0][3] = m03;
		mat4x4f[1][0] = m10; mat4x4f[1][1] = m11; mat4x4f[1][2] = m12; mat4x4f[1][3] = m13;
		mat4x4f[2][0] = m20; mat4x4f[2][1] = m21; mat4x4f[2][2] = m22; mat4x4f[2][3] = m23;
		mat4x4f[3][0] = m30; mat4x4f[3][1] = m31; mat4x4f[3][2] = m32; mat4x4f[3][3] = m33;
	}

	float* Matrix4x4f::operator[](unsigned int rowIndex)
	{
		ENTERNITY_ASSERT(rowIndex < 4);
		return mat4x4f[rowIndex];
	}

	Matrix4x4f Matrix4x4f::operator*(const Matrix4x4f& mat4)
	{
		Matrix4x4f res;

		res.mat4x4f[0][0] = mat4x4f[0][0] * mat4.mat4x4f[0][0] + mat4x4f[0][1] * mat4.mat4x4f[1][0] + mat4x4f[0][2] * mat4.mat4x4f[2][0] +
			mat4x4f[0][3] * mat4.mat4x4f[3][0];
		res.mat4x4f[0][1] = mat4x4f[0][0] * mat4.mat4x4f[0][1] + mat4x4f[0][1] * mat4.mat4x4f[1][1] + mat4x4f[0][2] * mat4.mat4x4f[2][1] +
			mat4x4f[0][3] * mat4.mat4x4f[3][1];
		res.mat4x4f[0][2] = mat4x4f[0][0] * mat4.mat4x4f[0][2] + mat4x4f[0][1] * mat4.mat4x4f[1][2] + mat4x4f[0][2] * mat4.mat4x4f[2][2] +
			mat4x4f[0][3] * mat4.mat4x4f[3][2];
		res.mat4x4f[0][3] = mat4x4f[0][0] * mat4.mat4x4f[0][3] + mat4x4f[0][1] * mat4.mat4x4f[1][3] + mat4x4f[0][2] * mat4.mat4x4f[2][3] +
			mat4x4f[0][3] * mat4.mat4x4f[3][3];

		res.mat4x4f[1][0] = mat4x4f[1][0] * mat4.mat4x4f[0][0] + mat4x4f[1][1] * mat4.mat4x4f[1][0] + mat4x4f[1][2] * mat4.mat4x4f[2][0] +
			mat4x4f[1][3] * mat4.mat4x4f[3][0];
		res.mat4x4f[1][1] = mat4x4f[1][0] * mat4.mat4x4f[0][1] + mat4x4f[1][1] * mat4.mat4x4f[1][1] + mat4x4f[1][2] * mat4.mat4x4f[2][1] +
			mat4x4f[1][3] * mat4.mat4x4f[3][1];
		res.mat4x4f[1][2] = mat4x4f[1][0] * mat4.mat4x4f[0][2] + mat4x4f[1][1] * mat4.mat4x4f[1][2] + mat4x4f[1][2] * mat4.mat4x4f[2][2] +
			mat4x4f[1][3] * mat4.mat4x4f[3][2];
		res.mat4x4f[1][3] = mat4x4f[1][0] * mat4.mat4x4f[0][3] + mat4x4f[1][1] * mat4.mat4x4f[1][3] + mat4x4f[1][2] * mat4.mat4x4f[2][3] +
			mat4x4f[1][3] * mat4.mat4x4f[3][3];

		res.mat4x4f[2][0] = mat4x4f[2][0] * mat4.mat4x4f[0][0] + mat4x4f[2][1] * mat4.mat4x4f[1][0] + mat4x4f[2][2] * mat4.mat4x4f[2][0] +
			mat4x4f[2][3] * mat4.mat4x4f[3][0];
		res.mat4x4f[2][1] = mat4x4f[2][0] * mat4.mat4x4f[0][1] + mat4x4f[2][1] * mat4.mat4x4f[1][1] + mat4x4f[2][2] * mat4.mat4x4f[2][1] +
			mat4x4f[2][3] * mat4.mat4x4f[3][1];
		res.mat4x4f[2][2] = mat4x4f[2][0] * mat4.mat4x4f[0][2] + mat4x4f[2][1] * mat4.mat4x4f[1][2] + mat4x4f[2][2] * mat4.mat4x4f[2][2] +
			mat4x4f[2][3] * mat4.mat4x4f[3][2];
		res.mat4x4f[2][3] = mat4x4f[2][0] * mat4.mat4x4f[0][3] + mat4x4f[2][1] * mat4.mat4x4f[1][3] + mat4x4f[2][2] * mat4.mat4x4f[2][3] +
			mat4x4f[2][3] * mat4.mat4x4f[3][3];

		res.mat4x4f[3][0] = mat4x4f[3][0] * mat4.mat4x4f[0][0] + mat4x4f[3][1] * mat4.mat4x4f[1][0] + mat4x4f[3][2] * mat4.mat4x4f[2][0] +
			mat4x4f[3][3] * mat4.mat4x4f[3][0];
		res.mat4x4f[3][1] = mat4x4f[3][0] * mat4.mat4x4f[0][1] + mat4x4f[3][1] * mat4.mat4x4f[1][1] + mat4x4f[3][2] * mat4.mat4x4f[2][1] +
			mat4x4f[3][3] * mat4.mat4x4f[3][1];
		res.mat4x4f[3][2] = mat4x4f[3][0] * mat4.mat4x4f[0][2] + mat4x4f[3][1] * mat4.mat4x4f[1][2] + mat4x4f[3][2] * mat4.mat4x4f[2][2] +
			mat4x4f[3][3] * mat4.mat4x4f[3][2];
		res.mat4x4f[3][3] = mat4x4f[3][0] * mat4.mat4x4f[0][3] + mat4x4f[3][1] * mat4.mat4x4f[1][3] + mat4x4f[3][2] * mat4.mat4x4f[2][3] +
			mat4x4f[3][3] * mat4.mat4x4f[3][3];

		return res;
	}

	Matrix4x4f Matrix4x4f::Translation(float transX, float transY, float transZ)
	{
		return Matrix4x4f(
			0.0f, 0.0f, 0.0f, transX,
			0.0f, 0.0f, 0.0f, transY,
			0.0f, 0.0f, 0.0f, transZ,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4x4f Matrix4x4f::Scale(float scaleX, float scaleY, float scaleZ)
	{
		return Matrix4x4f(
			scaleX, 0.0f, 0.0f, 0.0f,
			0.0f, scaleY, 0.0f, 0.0f,
			0.0f, 0.0f, scaleZ, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4x4f Matrix4x4f::Transpose(const Matrix4x4f& mat4)
	{
		return Matrix4x4f(
			mat4.mat4x4f[0][0], mat4.mat4x4f[1][0], mat4.mat4x4f[2][0], mat4.mat4x4f[3][0],
			mat4.mat4x4f[0][1], mat4.mat4x4f[1][1], mat4.mat4x4f[2][1], mat4.mat4x4f[3][1],
			mat4.mat4x4f[0][2], mat4.mat4x4f[1][2], mat4.mat4x4f[2][2], mat4.mat4x4f[3][2],
			mat4.mat4x4f[0][3], mat4.mat4x4f[1][3], mat4.mat4x4f[2][3], mat4.mat4x4f[3][3]);
	}

}