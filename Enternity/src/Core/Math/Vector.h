#pragma once
#include <cmath>

namespace Enternity
{
	template<typename T>
	struct Vector2
	{
		Vector2() {}
		Vector2(T _x, T _y) :x(_x), y(_y) {}
		union 
		{
			T x;
			T r;
		};
		
		union
		{
			T y;
			T g;
		};

		T length()
		{
			return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
		}

		Vector2 operator-()
		{
			return Vector2(-x, -y);
		}

		Vector2 operator+(const Vector2& other)
		{
			return Vector2(x + other.x, y + other.y);
		}

		void operator+=(const Vector2& other)
		{
			x += other.x;
			y += other.y;
		}

		Vector2 operator-(const Vector2& other)
		{
			return Vector2(x - other.x, y - other.y);
		}

		void operator-=(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;
		}

		Vector2 operator*(const Vector2& other)
		{
			return Vector2(x * other.x, y * other.y);
		}

		operator T*() { return &x; };
	};

	template<typename T>
	struct Vector3
	{
		Vector3() {}
		Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

		union
		{
			T x;
			T r;
		};

		union
		{
			T y;
			T g;
		};

		union
		{
			T z;
			T b;
		};

		T length()
		{
			return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
		}

		Vector3 operator-()
		{
			return Vector3(-x, -y, -z);
		}
		
		Vector3 operator+(const Vector3& other)
		{
			return Vector3(x + other.x, y + other.y, z + other.z);
		}

		void operator+=(const Vector3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
		}

		Vector3 operator-(const Vector3& other)
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}

		void operator-=(const Vector3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
		}

		Vector3 operator*(const Vector3& other)
		{
			return Vector3(x * other.x, y * other.y, z * other.z);
		}

		operator T*() { return &x; };
	};

	template<typename T>
	struct Vector4
	{
		Vector4() {}
		Vector4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}

		union
		{
			T x;
			T r;
		};

		union
		{
			T y;
			T g;
		};

		union
		{
			T z;
			T b;
		};

		union
		{
			T w;
			T a;
		};

		T length()
		{
			return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2));
		}

		Vector4 operator-()
		{
			return Vector4(-x, -y, -z, -w);
		}

		Vector4 operator+(const Vector4& other)
		{
			return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		void operator+=(const Vector4& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
		}

		Vector4 operator-(const Vector4& other)
		{
			return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		void operator-=(const Vector4& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
		}

		Vector4 operator*(const Vector4& other)
		{
			return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
		}

		operator T*() { return &x; };
	};

	typedef Vector2<float> Vector2f;
	typedef Vector3<float> Vector3f;
	typedef Vector4<float> Vector4f;

	typedef Vector2<double> Vector2d;
	typedef Vector3<double> Vector3d;
	typedef Vector4<double> Vector4d;
}