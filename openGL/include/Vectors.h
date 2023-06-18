#pragma once
#include <math.h>
#include <stdio.h>

class Vector4
{
public:
	float x, y, z, w;

	Vector4()
	{
		x = y = z = w = 0;
	}

	Vector4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	void set(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	float dot(Vector4 other)
	{
		return (x * other.x + y + other.y + z + other.x + w + other.w);
	}

	Vector4 cross(Vector4 other)
	{
		return Vector4(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x, 0);
	}

	Vector4 operator * (float s)
	{
		return Vector4(x * s, y * s, z * s, w * s);
	}

	Vector4 operator * (Vector4 other)
	{
		return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
	}

	Vector4 operator - (Vector4 other)
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	Vector4 operator + (Vector4 other)
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	Vector4 operator / (float s)
	{
		return Vector4(x / s, y / s, z / s, w / s);
	}

	Vector4 operator += (Vector4 other)
	{
		return Vector4(x += other.x, y += other.y, z += other.z, w += other.w);
	}

	Vector4 operator -= (Vector4 other)
	{
		return Vector4(x -= other.x, y -= other.y, z -= other.z, w -= other.w);
	}

	Vector4 operator *= (Vector4 other)
	{
		return Vector4(x *= other.x, y *= other.y, z *= other.z, w *= other.w);
	}
};

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(Vector4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	float Length()
	{
		return (float)sqrt(x * x + y * y + z * z);
	}

	void set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Normalize()
	{
		float norm = (float)sqrt(x*x + y*y + z*z);
		if (norm == 0.0)
		{
			printf("\n\nNormalize::Divisao por zero");
			x = 1;
			y = 1;
			z = 1;
			return;
		}
		x /= norm;
		y /= norm;
		z /= norm;
	}

	int Dot(const Vector3& v)
	{
		return(x * v.x + y * v.y + z * v.z);
	}

	void normalize()
	{
		float norm = (float)sqrt(x * x + y * y + z * z);
		x /= norm;
		y /= norm;
		z /= norm;
	}

	Vector3 operator * (const float s)
	{
		Vector3 aux(x * s, y * s, z * s);
		return(aux);
	}

	Vector3 operator *(const Vector3& v)
	{
		Vector3 aux(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
		return(aux);
	}

	Vector3 operator - (const Vector3& v)
	{
		Vector3 aux(x - v.x, y - v.y, z - v.z);
		return(aux);
	}

	Vector3 operator + (const Vector3& v)
	{
		Vector3 aux(x + v.x, y + v.y, z + v.z);
		return(aux);
	}
};

class Vector2
{
public:
	float x, y;

	Vector2()
	{
		x = y = 0;
	}

	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	Vector2(Vector3& other)
	{
		x = other.x;
		y = other.y;
	}

	Vector2(Vector3 other)
	{
		x = other.x;
		y = other.y;
	}

	Vector2(Vector4& other)
	{
		x = other.x;
		y = other.y;
	}

	Vector2(Vector4 other)
	{
		x = other.x;
		y = other.y;
	}

	void set(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	void normalize()
	{
		float norm = (float)sqrt(x * x + y * y);

		if (norm == 0.0)
		{
			printf("\n\nNormalize::Divisao por zero");
			x = 1;
			y = 1;
			return;
		}
		x /= norm;
		y /= norm;
	}

	Vector2 operator - (const Vector2& v)
	{
		Vector2 aux(x - v.x, y - v.y);
		return(aux);
	}

	Vector2 operator - (const Vector3& v)
	{
		Vector2 aux(x - v.x, y - v.y);
		return(aux);
	}

	Vector2 operator + (const Vector2& v)
	{
		Vector2 aux(x + v.x, y + v.y);
		return(aux);
	}

	Vector2 operator + (const Vector3& v)
	{
		Vector2 aux(x + v.x, y + v.y);
		return(aux);
	}

	Vector2 operator * (const float s)
	{
		Vector2 aux(x * s, y * s);
		return(aux);
	}

	Vector2 operator / (const float s)
	{
		Vector2 aux(x / s, y / s);
		return(aux);
	}
};