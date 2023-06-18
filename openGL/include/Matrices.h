#pragma once
#include "Vectors.h"

class Float2x2
{
	Vector2 a;
	Vector2 b;

	public:
		Float2x2();;

		void GenerateRotationMatrix(float angles);

		void GenerateScaleMatrix(float scale);

		Vector2 operator * (const Vector2& v)
		{
			Vector2 aux(a.x * v.x + b.x * v.y, a.y * v.x + b.y * v.y);
			return(aux);
		}

		Float2x2 operator * (const Float2x2& m)
		{
			Float2x2 aux;
			aux.a.x = a.x * m.a.x + b.x * m.a.y;
			aux.a.y = a.y * m.a.x + b.y * m.a.y;
			aux.b.x = a.x * m.b.x + b.x * m.b.y;
			aux.b.y = a.y * m.b.x + b.y * m.b.y;
			return(aux);
		}
};

class Float3x3
{
	public:
		
	Vector3 a;
	Vector3 b;
	Vector3 c;

		Float3x3();

		void GenerateRotateAroundMatrix(Vector3 axis, float angle);

		void GenerateScaleMatrix(float scale);

		Vector3 operator * (const Vector3& v)
		{
			Vector3 aux(a.x * v.x + b.x * v.y + c.x * v.z, a.y * v.x + b.y * v.y + c.y * v.z, a.z * v.x + b.z * v.y + c.z * v.z);
			return(aux);
		}

		Float3x3 operator * (const Float3x3& m)
		{
			Float3x3 aux;
			aux.a.x = a.x * m.a.x + b.x * m.a.y + c.x * m.a.z;
			aux.a.y = a.y * m.a.x + b.y * m.a.y + c.y * m.a.z;
			aux.a.z = a.z * m.a.x + b.z * m.a.y + c.z * m.a.z;
			aux.b.x = a.x * m.b.x + b.x * m.b.y + c.x * m.b.z;
			aux.b.y = a.y * m.b.x + b.y * m.b.y + c.y * m.b.z;
			aux.b.z = a.z * m.b.x + b.z * m.b.y + c.z * m.b.z;
			aux.c.x = a.x * m.c.x + b.x * m.c.y + c.x * m.c.z;
			aux.c.y = a.y * m.c.x + b.y * m.c.y + c.y * m.c.z;
			aux.c.z = a.z * m.c.x + b.z * m.c.y + c.z * m.c.z;
			return(aux);
		}
};

class Float4x4
{
public:
	Vector4 a, b, c, d;

	Float4x4();;
	
	Float4x4(Float3x3& other);
	
	Float4x4(Vector4& a, Vector4& b, Vector4& c, Vector4& d);
	
	void GeneratePerpectiveMatrix(float min, float max);

	void GenerateTranslationMatrix(float x, float y, float z);

	void GenerateScaleMatrix(float scale);

	void GenerateRotationMatrix(Vector3 axis, float angle);

	void GenerateLookAt(Vector3 eye, Vector3 center, Vector3 up);

	Float4x4 Transpose();

	Vector4 operator * (const Vector4& v)
	{
		Vector4 aux(a.x * v.x + a.y * v.y + a.z * v.z + a.w * v.w,
					b.x * v.x + b.y * v.y + b.z * v.z + b.w * v.w,
					c.x * v.x + c.y * v.y + c.z * v.z + c.w * v.w,
					d.x * v.x + d.y * v.y + d.z * v.z + d.w * v.w);

		return aux;
	}

	Float4x4 operator * (const Float4x4& m)
	{
		Float4x4 aux;

		aux.a.set(a.x * m.a.x + a.y * m.b.x + a.z * m.c.x + a.w * m.d.x,
					a.x * m.a.y + a.y * m.b.y + a.z * m.c.y + a.w * m.d.y,
					a.x * m.a.z + a.y * m.b.z + a.z * m.c.z + a.w * m.d.z,
					a.x * m.a.w + a.y * m.b.w + a.z * m.c.w + a.w * m.d.w);

		aux.b.set(b.x * m.a.x + b.y * m.b.x + b.z * m.c.x + b.w * m.d.x,
					b.x * m.a.y + b.y * m.b.y + b.z * m.c.y + b.w * m.d.y,
					b.x * m.a.z + b.y * m.b.z + b.z * m.c.z + b.w * m.d.z,
					b.x * m.a.w + b.y * m.b.w + b.z * m.c.w + b.w * m.d.w);

		aux.c.set(c.x * m.a.x + c.y * m.b.x + c.z * m.c.x + c.w * m.d.x,
					c.x * m.a.y + c.y * m.b.y + c.z * m.c.y + c.w * m.d.y,
					c.x * m.a.z + c.y * m.b.z + c.z * m.c.z + c.w * m.d.z,
					c.x * m.a.w + c.y * m.b.w + c.z * m.c.w + c.w * m.d.w);

		aux.d.set(d.x * m.a.x + d.y * m.b.x + d.z * m.c.x + d.w * m.d.x,
					d.x * m.a.y + d.y * m.b.y + d.z * m.c.y + d.w * m.d.y,
					d.x * m.a.z + d.y * m.b.z + d.z * m.c.z + d.w * m.d.z,
					d.x * m.a.w + d.y * m.b.w + d.z * m.c.w + d.w * m.d.w);

		return(aux);
	}
};
