/***************************************************************************************
Author: lvke
Date:2023/2/6 22:59
Description:
Matrix 4x4  row-major
****************************************************************************************/
#pragma once

namespace Enternity
{
	class Matrix4x4f
	{
	public:
		Matrix4x4f();
		Matrix4x4f(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);
		
		float* operator[](unsigned int rowIndex);
		Matrix4x4f operator*(const Matrix4x4f& mat4);

	
		//some static functions
		static Matrix4x4f Translate(float transX, float transY, float transZ);
		//Rotate around x, y, z, the unit is the angle
		static Matrix4x4f Rotate(float rotateX, float rotateY, float rotateZ);
		static Matrix4x4f Scale(float scaleX, float scaleY, float scaleZ);
		static Matrix4x4f Perspective(float radian, float aspect, float nearZ, float farZ);

		static Matrix4x4f Transpose(const Matrix4x4f& mat4);
		static Matrix4x4f Inverse(const  Matrix4x4f& mat4);
		
		//some static variables
		static Matrix4x4f IDENTITY;
		static Matrix4x4f ZERO;
	private:
		float m_mat4x4f[4][4];
	};

}

