#ifndef VERTEX_HPP
#define VERTEX_HPP

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

	inline const Vector2<T>& normalize()
	{
		T len = length();

		x /= len;
		y /= len;

		return *this;
	}

	inline const Vector2<T>& normalized() const
	{
		T len = length();
		return Vector2<T>(x / len, y / len);
	}

	inline T length() const
	{
		return sqrt((x * x) + (y * y));
	}

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

	inline const Vector3<T>& normalize()
	{
		T len = length();

		x /= len;
		y /= len;
		z /= len;

		return *this;
	}

	inline const Vector3<T>& normalized() const
	{
		T len = length();
		return Vector3<T>(x / len, y / len, z / len);
	}

	inline T length() const
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}


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

	inline const Vector4<T>& normalize()
	{
		T len = length();

		x /= len;
		y /= len;
		z /= len;
		w /= len;

		return *this;
	}

	inline const Vector4<T>& normalized() const
	{
		T len = length();
		return Vector4<T>(x / len, y / len, z / len, w / len);
	}

	inline T length() const
	{
		return sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}

	inline const Vector4<T>& operator=(const Vector4<T>& v)
	{
		x = v.x; y = v.y; z = v.z; w = v.w;
		return *this;
	};

	inline float operator[](unsigned int index)
	{
		if (index == 0)
		{
			return x;
		}

		if (index == 1)
		{
			return y;
		}

		if (index == 2)
		{
			return z;
		}

		if (index == 3)
		{
			return w;
		}

		else
			return 0;
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
	T row[4][4];

	Matrix4()
	{
		row[0][0] = 1; row[0][1] = 0; row[0][2] = 0; row[0][3] = 0;
		row[1][0] = 0; row[1][1] = 1; row[1][2] = 0; row[1][3] = 0;
		row[2][0] = 0; row[2][1] = 0; row[2][2] = 1; row[2][3] = 0;
		row[3][0] = 0; row[3][1] = 0; row[3][2] = 0; row[3][3] = 1;
	}

	Matrix4(const Vector4<T>& row1,
		const Vector4<T>& row2,
		const Vector4<T>& row3,
		const Vector4<T>& row4)
	{
		row[0][0] = row1.x; row[0][1] = row1.y; row[0][2] = row1.z; row[0][3] = row1.w;
		row[1][0] = row2.x; row[1][1] = row2.y; row[1][2] = row2.z; row[1][3] = row2.w;
		row[2][0] = row3.x; row[2][1] = row3.y; row[2][2] = row3.z; row[2][3] = row3.w;
		row[3][0] = row4.x; row[3][1] = row4.y; row[3][2] = row4.z; row[3][3] = row4.w;
	}

	Matrix4(const Matrix4<T>& m)
	{
		row[0][0] = m.row[0][0]; row[0][1] = m.row[0][1]; row[0][2] = m.row[0][2]; row[0][3] = m.row[0][3];
		row[1][0] = m.row[1][0]; row[1][1] = m.row[1][1]; row[1][2] = m.row[1][2]; row[1][3] = m.row[1][3];
		row[2][0] = m.row[2][0]; row[2][1] = m.row[2][1]; row[2][2] = m.row[2][2]; row[2][3] = m.row[2][3];
		row[3][0] = m.row[3][0]; row[3][1] = m.row[3][1]; row[3][2] = m.row[3][2]; row[3][3] = m.row[3][3];
	}

	void initTranslation(const Vector3<T>& v)
	{
		row[3][0] = v.x;
		row[3][1] = v.y;
		row[3][2] = v.z;
	}

	void initRotation(T angle, const Vector3<T>& axis)
	{
		axis.normalize();
		T xAngle = angle * axis.x;
		T yAngle = angle * axis.y;
		T zAngle = angle * axis.z;

		row[0][0] = cos(yAngle) * cos(zAngle); row[0][1] = cos(zAngle) * sin(xAngle) * sin(yAngle) - cos(xAngle) * sin(zAngle); row[0][2] = cos(xAngle) * cos(zAngle) * sin(yAngle) + sin(xAngle) * sin(zAngle);  row[0][3] = 0;
		row[1][0] = cos(yAngle) * sin(zAngle); row[1][1] = cos(xAngle) * cos(zAngle) + sin(xAngle) * sin(yAngle) * sin(zAngle); row[1][2] = -cos(zAngle) * sin(xAngle) + cos(xAngle) * sin(yAngle) * sin(zAngle); row[1][3] = 0;
		row[2][0] = -sin(yAngle);              row[2][1] = cos(yAngle) * sin(xAngle);                                           row[2][2] = cos(xAngle) * cos(yAngle);                                            row[2][3] = 0;
		row[3][0] = 0;                         row[3][1] = 0;                                                                   row[3][2] = 0;                                                                    row[3][3] = 1;
	}

	void initPerspective()
	{

	}

	const Matrix4<T>& operator=(const  Matrix4<T>& m)
	{
		row[0][0] = m.row[0][0]; row[0][1] = m.row[0][1]; row[0][2] = m.row[0][2]; row[0][3] = m.row[0][3];
		row[1][0] = m.row[1][0]; row[1][1] = m.row[1][1]; row[1][2] = m.row[1][2]; row[1][3] = m.row[1][3];
		row[2][0] = m.row[2][0]; row[2][1] = m.row[2][1]; row[2][2] = m.row[2][2]; row[2][3] = m.row[2][3];
		row[3][0] = m.row[3][0]; row[3][1] = m.row[3][1]; row[3][2] = m.row[3][2]; row[3][3] = m.row[3][3];

		return *this;
	}

	const  Matrix4<T>& operator*(const  Matrix4<T>& m) const
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				row[j][i] = row[j][0] * m.row[0][i] +
							row[j][1] * m.row[1][i] +
							row[j][2] * m.row[2][i] +
							row[j][3] * m.row[3][i];
			}
		}

		return *this;
	}

	void printToConsole() const
	{

	}
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

#endif // MATH_HPP