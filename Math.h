#ifndef VERTEX_H
#define VERTEX_H

#define PI 3.141592

#define TO_RADIANS(a) (float)((a) * PI / 180)
#define TO_DEGREES(a) (float)((a) * 180 / PI)

template<typename T>
struct Vector2
{
	T x, y;

	Vector2() : x(0), y(0) {}
	Vector2(T _x, T _y) : x(_x), y(_y) {}

	Vector2(const Vector2<T>& v) : x(v.x), y(v.y) {}

	inline const Vector2<T>& operator=(const Vector2<T>& v)
	{
		x = v.x; y = v.y; 
		return *this;
	};

	inline float operator[](unsigned int index) const
	{
		return (&x)[index];
	}
};

template<typename T>
struct Vector3
{
	T x, y, z;

	Vector3() : x(0), y(0), z(0) {}
	Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

	Vector3(const Vector3<T>& v) : x(v.x), y(v.y), z(v.z) {}

	inline const Vector3<T>& operator=(const Vector3<T>& v)
	{
		x = v.x; y = v.y; z = v.z; return *this;
	};

	inline float operator[](unsigned int index) const
	{
		return (&x)[index];
	}
};

template<typename T>
struct Vector4
{
	T x, y, z, w;

	Vector4() : x(0), y(0), z(0), w(0) {}
	Vector4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}

	Vector4(const Vector4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

	inline const Vector4<T>& operator=(const Vector4<T>& v)
	{
		x = v.x; y = v.y; z = v.z; w = v.w;
		return *this;
	};

	inline float operator[](unsigned int index) const
	{
		return (&x)[index];
	}
};

using Vector2b = Vector2<char>;
using Vector2s = Vector2<short>;
using Vector2i = Vector2<int>;
using Vector2l = Vector2<long>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;

using Vector3b = Vector3<char>;
using Vector3s = Vector3<short>;
using Vector3i = Vector3<int>;
using Vector3l = Vector3<long>;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;

using Vector4b = Vector4<char>;
using Vector4s = Vector4<short>;
using Vector4i = Vector4<int>;
using Vector4l = Vector4<long>;
using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;

template <typename T>
struct Matrix4
{
	Vector4<T> col[4];

	Matrix4() : 
		col[0](1, 0, 0, 0),
		col[1](0, 1, 0, 0),
		col[2](0, 0, 1, 0),
		col[3](0, 0, 0, 1) {}

	Matrix4(const Vector4<T>& col1,
		    const Vector4<T>& col2,
		    const Vector4<T>& col3,
		    const Vector4<T>& col4) :
		col[0](col1),
		col[1](col2),
		col[2](col3),
		col[3](col4) {}

	Matrix4(const Matrix4<T>& m) :
		col[0](m.col[0]),
		col[1](m.col[1]),
		col[2](m.col[2]),
		col[3](m.col[3]) {}

	// todo: IMPLEMENT
	void translate(const Vector3<T>& v);
	void rotate(T angle, const Vector3<T>& axis);
	void perspective();

	const Matrix4<T>& operator=(const  Matrix4<T>& m);
	const  Matrix4<T>& operator*(const  Matrix4<T>& m) const;

	void printToConsole() const;
};

using Matrix4f = Matrix4<float>;
using Matrix4d = Matrix4<double>;

struct Vertex
{
	Vector3f pos;
	Vector2f texCoord;
	//Vector3f norm;

	Vertex() : pos(), texCoord() {}
	Vertex(Vector3f _pos, Vector2f _texCoord) : pos(_pos), texCoord(_texCoord) {}
};

#endif