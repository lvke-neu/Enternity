#pragma once

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

		Vector2 operator-()
		{
			return Vector2(-x, -y);
		}
	};

	template<typename T>
	struct Vector3 : public Vector2<T>
	{
		Vector3() {}
		Vector3(T _x, T _y, T _z) : Vector2<T>(_x, _y), z(_z) {}

		union
		{
			T z;
			T b;
		};

	
	};

	template<typename T>
	struct Vector4 : public Vector3<T>
	{
		Vector4() {}
		Vector4(T _x, T _y, T _z, T _w) : Vector3<T>(_x, _y, _z), w(_w) {}

		union
		{
			T w;
			T a;
		};


	};

	typedef Vector2<float> Vector2f;
	typedef Vector3<float> Vector3f;
	typedef Vector4<float> Vector4f;

	typedef Vector2<double> Vector2d;
	typedef Vector3<double> Vector3d;
	typedef Vector4<double> Vector4d;
}