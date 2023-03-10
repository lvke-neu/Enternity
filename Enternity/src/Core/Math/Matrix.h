#pragma once

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
	};


	typedef Matrix<float, 4, 4> Matrix4x4f;
	typedef Matrix<double, 4, 4> Matrix4x4d;

	void MatrixRotationYawPitchRoll(Matrix4x4f& matrix, float yaw, float pitch, float roll);
}