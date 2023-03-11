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

}