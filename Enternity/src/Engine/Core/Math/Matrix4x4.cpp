#include "Matrix4x4.h"
#include "../Basic/Macro.h"

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
		m_mat4x4f[0][0] = m00; m_mat4x4f[0][1] = m01; m_mat4x4f[0][2] = m02; m_mat4x4f[0][3] = m03;
		m_mat4x4f[1][0] = m10; m_mat4x4f[1][1] = m11; m_mat4x4f[1][2] = m12; m_mat4x4f[1][3] = m13;
		m_mat4x4f[2][0] = m20; m_mat4x4f[2][1] = m21; m_mat4x4f[2][2] = m22; m_mat4x4f[2][3] = m23;
		m_mat4x4f[3][0] = m30; m_mat4x4f[3][1] = m31; m_mat4x4f[3][2] = m32; m_mat4x4f[3][3] = m33;
	}

	float* Matrix4x4f::operator[](unsigned int rowIndex)
	{
		ENTERNITY_ASSERT(rowIndex < 4);
		return m_mat4x4f[rowIndex];
	}

	Matrix4x4f Matrix4x4f::operator*(const Matrix4x4f& mat4)
	{
		Matrix4x4f res;

		res.m_mat4x4f[0][0] = m_mat4x4f[0][0] * mat4.m_mat4x4f[0][0] + m_mat4x4f[0][1] * mat4.m_mat4x4f[1][0] + m_mat4x4f[0][2] * mat4.m_mat4x4f[2][0] +
			m_mat4x4f[0][3] * mat4.m_mat4x4f[3][0];
		res.m_mat4x4f[0][1] = m_mat4x4f[0][0] * mat4.m_mat4x4f[0][1] + m_mat4x4f[0][1] * mat4.m_mat4x4f[1][1] + m_mat4x4f[0][2] * mat4.m_mat4x4f[2][1] +
			m_mat4x4f[0][3] * mat4.m_mat4x4f[3][1];
		res.m_mat4x4f[0][2] = m_mat4x4f[0][0] * mat4.m_mat4x4f[0][2] + m_mat4x4f[0][1] * mat4.m_mat4x4f[1][2] + m_mat4x4f[0][2] * mat4.m_mat4x4f[2][2] +
			m_mat4x4f[0][3] * mat4.m_mat4x4f[3][2];
		res.m_mat4x4f[0][3] = m_mat4x4f[0][0] * mat4.m_mat4x4f[0][3] + m_mat4x4f[0][1] * mat4.m_mat4x4f[1][3] + m_mat4x4f[0][2] * mat4.m_mat4x4f[2][3] +
			m_mat4x4f[0][3] * mat4.m_mat4x4f[3][3];

		res.m_mat4x4f[1][0] = m_mat4x4f[1][0] * mat4.m_mat4x4f[0][0] + m_mat4x4f[1][1] * mat4.m_mat4x4f[1][0] + m_mat4x4f[1][2] * mat4.m_mat4x4f[2][0] +
			m_mat4x4f[1][3] * mat4.m_mat4x4f[3][0];
		res.m_mat4x4f[1][1] = m_mat4x4f[1][0] * mat4.m_mat4x4f[0][1] + m_mat4x4f[1][1] * mat4.m_mat4x4f[1][1] + m_mat4x4f[1][2] * mat4.m_mat4x4f[2][1] +
			m_mat4x4f[1][3] * mat4.m_mat4x4f[3][1];
		res.m_mat4x4f[1][2] = m_mat4x4f[1][0] * mat4.m_mat4x4f[0][2] + m_mat4x4f[1][1] * mat4.m_mat4x4f[1][2] + m_mat4x4f[1][2] * mat4.m_mat4x4f[2][2] +
			m_mat4x4f[1][3] * mat4.m_mat4x4f[3][2];
		res.m_mat4x4f[1][3] = m_mat4x4f[1][0] * mat4.m_mat4x4f[0][3] + m_mat4x4f[1][1] * mat4.m_mat4x4f[1][3] + m_mat4x4f[1][2] * mat4.m_mat4x4f[2][3] +
			m_mat4x4f[1][3] * mat4.m_mat4x4f[3][3];

		res.m_mat4x4f[2][0] = m_mat4x4f[2][0] * mat4.m_mat4x4f[0][0] + m_mat4x4f[2][1] * mat4.m_mat4x4f[1][0] + m_mat4x4f[2][2] * mat4.m_mat4x4f[2][0] +
			m_mat4x4f[2][3] * mat4.m_mat4x4f[3][0];
		res.m_mat4x4f[2][1] = m_mat4x4f[2][0] * mat4.m_mat4x4f[0][1] + m_mat4x4f[2][1] * mat4.m_mat4x4f[1][1] + m_mat4x4f[2][2] * mat4.m_mat4x4f[2][1] +
			m_mat4x4f[2][3] * mat4.m_mat4x4f[3][1];
		res.m_mat4x4f[2][2] = m_mat4x4f[2][0] * mat4.m_mat4x4f[0][2] + m_mat4x4f[2][1] * mat4.m_mat4x4f[1][2] + m_mat4x4f[2][2] * mat4.m_mat4x4f[2][2] +
			m_mat4x4f[2][3] * mat4.m_mat4x4f[3][2];
		res.m_mat4x4f[2][3] = m_mat4x4f[2][0] * mat4.m_mat4x4f[0][3] + m_mat4x4f[2][1] * mat4.m_mat4x4f[1][3] + m_mat4x4f[2][2] * mat4.m_mat4x4f[2][3] +
			m_mat4x4f[2][3] * mat4.m_mat4x4f[3][3];

		res.m_mat4x4f[3][0] = m_mat4x4f[3][0] * mat4.m_mat4x4f[0][0] + m_mat4x4f[3][1] * mat4.m_mat4x4f[1][0] + m_mat4x4f[3][2] * mat4.m_mat4x4f[2][0] +
			m_mat4x4f[3][3] * mat4.m_mat4x4f[3][0];
		res.m_mat4x4f[3][1] = m_mat4x4f[3][0] * mat4.m_mat4x4f[0][1] + m_mat4x4f[3][1] * mat4.m_mat4x4f[1][1] + m_mat4x4f[3][2] * mat4.m_mat4x4f[2][1] +
			m_mat4x4f[3][3] * mat4.m_mat4x4f[3][1];
		res.m_mat4x4f[3][2] = m_mat4x4f[3][0] * mat4.m_mat4x4f[0][2] + m_mat4x4f[3][1] * mat4.m_mat4x4f[1][2] + m_mat4x4f[3][2] * mat4.m_mat4x4f[2][2] +
			m_mat4x4f[3][3] * mat4.m_mat4x4f[3][2];
		res.m_mat4x4f[3][3] = m_mat4x4f[3][0] * mat4.m_mat4x4f[0][3] + m_mat4x4f[3][1] * mat4.m_mat4x4f[1][3] + m_mat4x4f[3][2] * mat4.m_mat4x4f[2][3] +
			m_mat4x4f[3][3] * mat4.m_mat4x4f[3][3];

		return res;
	}

	Matrix4x4f Matrix4x4f::Translate(float transX, float transY, float transZ)
	{
		return Matrix4x4f(
			0.0f, 0.0f, 0.0f, transX,
			0.0f, 0.0f, 0.0f, transY,
			0.0f, 0.0f, 0.0f, transZ,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4x4f Matrix4x4f::Rotate(float rotateX, float rotateY, float rotateZ)
	{
		return IDENTITY;
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
			mat4.m_mat4x4f[0][0], mat4.m_mat4x4f[1][0], mat4.m_mat4x4f[2][0], mat4.m_mat4x4f[3][0],
			mat4.m_mat4x4f[0][1], mat4.m_mat4x4f[1][1], mat4.m_mat4x4f[2][1], mat4.m_mat4x4f[3][1],
			mat4.m_mat4x4f[0][2], mat4.m_mat4x4f[1][2], mat4.m_mat4x4f[2][2], mat4.m_mat4x4f[3][2],
			mat4.m_mat4x4f[0][3], mat4.m_mat4x4f[1][3], mat4.m_mat4x4f[2][3], mat4.m_mat4x4f[3][3]);
	}

	Matrix4x4f Matrix4x4f::Inverse(const Matrix4x4f& mat4)
	{
		float m00 = mat4.m_mat4x4f[0][0], m01 = mat4.m_mat4x4f[0][1], m02 = mat4.m_mat4x4f[0][2], m03 = mat4.m_mat4x4f[0][3];
		float m10 = mat4.m_mat4x4f[1][0], m11 = mat4.m_mat4x4f[1][1], m12 = mat4.m_mat4x4f[1][2], m13 = mat4.m_mat4x4f[1][3];
		float m20 = mat4.m_mat4x4f[2][0], m21 = mat4.m_mat4x4f[2][1], m22 = mat4.m_mat4x4f[2][2], m23 = mat4.m_mat4x4f[2][3];
		float m30 = mat4.m_mat4x4f[3][0], m31 = mat4.m_mat4x4f[3][1], m32 = mat4.m_mat4x4f[3][2], m33 = mat4.m_mat4x4f[3][3];

		float v0 = m20 * m31 - m21 * m30;
		float v1 = m20 * m32 - m22 * m30;
		float v2 = m20 * m33 - m23 * m30;
		float v3 = m21 * m32 - m22 * m31;
		float v4 = m21 * m33 - m23 * m31;
		float v5 = m22 * m33 - m23 * m32;

		float t00 = +(v5 * m11 - v4 * m12 + v3 * m13);
		float t10 = -(v5 * m10 - v2 * m12 + v1 * m13);
		float t20 = +(v4 * m10 - v2 * m11 + v0 * m13);
		float t30 = -(v3 * m10 - v1 * m11 + v0 * m12);

		float invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

		float d00 = t00 * invDet;
		float d10 = t10 * invDet;
		float d20 = t20 * invDet;
		float d30 = t30 * invDet;

		float d01 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		float d11 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		float d21 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		float d31 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		v0 = m10 * m31 - m11 * m30;
		v1 = m10 * m32 - m12 * m30;
		v2 = m10 * m33 - m13 * m30;
		v3 = m11 * m32 - m12 * m31;
		v4 = m11 * m33 - m13 * m31;
		v5 = m12 * m33 - m13 * m32;

		float d02 = +(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		float d12 = -(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		float d22 = +(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		float d32 = -(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		v0 = m21 * m10 - m20 * m11;
		v1 = m22 * m10 - m20 * m12;
		v2 = m23 * m10 - m20 * m13;
		v3 = m22 * m11 - m21 * m12;
		v4 = m23 * m11 - m21 * m13;
		v5 = m23 * m12 - m22 * m13;

		float d03 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		float d13 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		float d23 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		float d33 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		return Matrix4x4f(
			d00, d01, d02, d03, 
			d10, d11, d12, d13, 
			d20, d21, d22, d23, 
			d30, d31, d32, d33);
	}

}