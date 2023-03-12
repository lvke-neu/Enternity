#pragma once
#include "Math.h"

namespace Enternity
{
	template <typename T, int ROWS, int COLS>
	struct Matrix
	{
		union {
			T data[ROWS][COLS];
		};

		auto operator[](int row_index) {
			return data[row_index];
		}

		const auto  operator[](int row_index) const {
			return data[row_index];
		}

		operator T*() { return &data[0][0]; };
		operator const T*() const { return static_cast<const T*>(&data[0][0]); };

		Matrix operator+(const Matrix& other)
		{
			Matrix result;
			for (int i = 0; i < ROWS; i++)
				for (int j = 0; j < COLS; j++)
				{
					result[i][j] = data[i][j] + other[i][j];
				}
			return result;
		}

		void operator+=(const Matrix& other)
		{
			for (int i = 0; i < ROWS; i++)
				for (int j = 0; j < COLS; j++)
				{
					data[i][j] += other[i][j];
				}
		}

		Matrix operator-(const Matrix& other)
		{
			Matrix result;
			for (int i = 0; i < ROWS; i++)
				for (int j = 0; j < COLS; j++)
				{
					result[i][j] = data[i][j] - other[i][j];
				}
			return result;
		}

		void operator-=(const Matrix& other)
		{
			for (int i = 0; i < ROWS; i++)
				for (int j = 0; j < COLS; j++)
				{
					data[i][j] -= other[i][j];
				}
		}

		Matrix operator*(const Matrix& other)
		{
			Matrix result;
			for (int i = 0; i < ROWS; i++)
				for (int j = 0; j < COLS; j++)
				{
					result[i][j] = 0;
					for (int k = 0; k < ROWS; k++)
					{
						result[i][j] += data[i][k] * other[k][j];
					}
				}
			return result;
		}

		static Matrix Identity()
		{
			Matrix result;
			for (int i = 0; i < ROWS; i++)
			{
				for (int j = 0; j < COLS; j++)
				{
					result[i][j] = i == j ? (T)1 : (T)0;
				}
			}

			return result;
		}

		static Matrix Zero()
		{
			Matrix result;
			for (int i = 0; i < ROWS; i++)
			{
				for (int j = 0; j < COLS; j++)
				{
					result[i][j] = 0;
				}
			}

			return result;
		}
	};

	typedef Matrix<float, 4, 4> Matrix4x4f;
	typedef Matrix<double, 4, 4> Matrix4x4d;

	template<typename T>
	void Matrix4x4Translate(Matrix<T, 4, 4>& matrix, T Tx, T Ty, T Tz)
	{
		matrix = Matrix<T, 4, 4>::Identity();
		matrix[0][3] = Tx;
		matrix[1][3] = Ty;
		matrix[2][3] = Tz;
	}

	template<typename T>
	void Matrix4x4RotateYawPitchRoll(Matrix<T, 4, 4>& matrix, T yaw, T pitch, T roll, bool isRadian)
	{
		if (!isRadian)
		{
			yaw = (T)Math::AngleToRadian(yaw);
			pitch = (T)Math::AngleToRadian(pitch);
			roll = (T)Math::AngleToRadian(roll);
		}

		float cYaw, cPitch, cRoll, sYaw, sPitch, sRoll;

		// Get the cosine and sin of the yaw, pitch, and roll.
		cYaw = std::cos(yaw);
		cPitch = std::cos(pitch);
		cRoll = std::cos(roll);

		sYaw = std::sin(yaw);
		sPitch = std::sin(pitch);
		sRoll = std::sin(roll);

		// Calculate the yaw, pitch, roll rotation matrix.
		Matrix4x4f tmp = {
			(cRoll * cYaw) + (sRoll * sPitch * sYaw), (sRoll * cPitch), (cRoll * -sYaw) + (sRoll * sPitch * cYaw), 0.0f ,
			(-sRoll * cYaw) + (cRoll * sPitch * sYaw), (cRoll * cPitch), (sRoll * sYaw) + (cRoll * sPitch * cYaw), 0.0f,
			(cPitch * sYaw), -sPitch, (cPitch * cYaw), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		matrix = tmp;

		return;
	}


	template<typename T>
	void Matrix4x4Scale(Matrix<T, 4, 4>& matrix, T Sx, T Sy, T Sz)
	{
		matrix = Matrix<T, 4, 4>::Identity();
		matrix[0][0] = Sx;
		matrix[1][1] = Sy;
		matrix[2][2] = Sz;
	}

	template<typename T>
	void Matrix4x4Perspective(Matrix<T, 4, 4>& matrix, T fov, T aspect, T nearZ, T farZ, bool isRadian)
	{
		if (!isRadian)
		{
			fov = (T)Math::AngleToRadian(fov);
		}
		
		T tan_half_fovy = std::tan(fov / 2);
		matrix = Matrix<T, 4, 4>::Zero();
		matrix[0][0] = 1.f / (aspect * tan_half_fovy);
		matrix[1][1] = 1.f / tan_half_fovy;
		matrix[2][2] = farZ / (nearZ - farZ);
		matrix[3][2] = -1.f;
		matrix[2][3] = -(farZ * nearZ) / (farZ - nearZ);
	}

	template<typename T>
	Matrix<T, 4, 4> Matrix4x4Inverse(const Matrix<T, 4, 4>& matrix)
	{
		float m00 = matrix[0][0], m01 = matrix[0][1], m02 = matrix[0][2], m03 = matrix[0][3];
		float m10 = matrix[1][0], m11 = matrix[1][1], m12 = matrix[1][2], m13 = matrix[1][3];
		float m20 = matrix[2][0], m21 = matrix[2][1], m22 = matrix[2][2], m23 = matrix[2][3];
		float m30 = matrix[3][0], m31 = matrix[3][1], m32 = matrix[3][2], m33 = matrix[3][3];

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

		Matrix<T, 4, 4> tmp = {
			d00, d01, d02, d03,
			d10, d11, d12, d13,
			d20, d21, d22, d23,
			d30, d31, d32, d33 };

		return tmp;
	}
	
}