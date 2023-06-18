#include "Matrices.h"

Float2x2::Float2x2()
{
	a.set(1, 0);
	b.set(0, 1);
}

void Float2x2::GenerateRotationMatrix(float angles)
{
	a.set(cos(angles), -sin(angles));
	b.set(sin(angles), cos(angles));
}

void Float2x2::GenerateScaleMatrix(float scale)
{
	a.set(scale, 0);
	b.set(0, scale);
}

Float3x3::Float3x3()
{
	a.set(1, 0, 0);
	b.set(0, 1, 0);
	c.set(0, 0, 1);
}

void Float3x3::GenerateRotateAroundMatrix(Vector3 axis, float angle)
{
	//considerando a,b,c,d como linhas, crie a matriz de rotação em torno de um eixo
	//axis é o vetor que representa o eixo
	//angle é o ângulo de rotação

	a.set(cos(angle) + axis.x * axis.x * (1 - cos(angle)), axis.x * axis.y * (1 - cos(angle)) - axis.z * sin(angle), axis.x * axis.z * (1 - cos(angle)) + axis.y * sin(angle));
	b.set(axis.y * axis.x * (1 - cos(angle)) + axis.z * sin(angle), cos(angle) + axis.y * axis.y * (1 - cos(angle)), axis.y * axis.z * (1 - cos(angle)) - axis.x * sin(angle));
	c.set(axis.z * axis.x * (1 - cos(angle)) - axis.y * sin(angle), axis.z * axis.y * (1 - cos(angle)) + axis.x * sin(angle), cos(angle) + axis.z * axis.z * (1 - cos(angle)));
}

void Float3x3::GenerateScaleMatrix(float scale)
{
	a.set(scale, 0, 0);
	b.set(0, scale, 0);
	c.set(0, 0, scale);
}

Float4x4::Float4x4()
{
	a.set(1, 0, 0, 0);
	b.set(0, 1, 0, 0);
	c.set(0, 0, 1, 0);
	d.set(0, 0, 0, 1);
}

Float4x4::Float4x4(Float3x3& other)
{
	a.set(other.a.x, other.a.y, other.a.z, 0);
	b.set(other.b.x, other.b.y, other.b.z, 0);
	c.set(other.c.x, other.c.y, other.c.z, 0);
	d.set(0, 0, 0, 1);
}

Float4x4::Float4x4(Vector4& a, Vector4& b, Vector4& c, Vector4& d)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
}

void Float4x4::GeneratePerpectiveMatrix(float min, float max)
{
	a.set(1, 0, 0, 0);
	b.set(0, 1, 0, 0);
	c.set(0, 0, 1, 0);
	d.set(0, 0, -1.0 / min, 0);
}

void Float4x4::GenerateTranslationMatrix(float x, float y, float z)
{
	a.set(1, 0, 0, x);
	b.set(0, 1, 0, y);
	c.set(0, 0, 1, z);
	d.set(0, 0, 0, 1);
}

void Float4x4::GenerateScaleMatrix(float scale)
{
	Float3x3 aux;
	aux.GenerateScaleMatrix(scale);
	*this = aux;
}

void Float4x4::GenerateRotationMatrix(Vector3 axis, float angle)
{
	Float3x3 aux;
	aux.GenerateRotateAroundMatrix(axis, angle);
	*this = aux;
}

void Float4x4::GenerateLookAt(Vector3 eye, Vector3 center, Vector3 up)
{
	Vector3 direction = center - eye;
	direction.normalize();

	Vector3 right = direction * up;
	right.normalize();

	Vector3 newUp = right * direction;

	a.set(right.x, right.y, right.z, -center.x);
	b.set(newUp.x, newUp.y, newUp.z, -center.y);
	c.set(direction.x, direction.y, direction.z, -center.z);
	d.set(0, 0, 0, 1);
}

Float4x4 Float4x4::Transpose()
{
	Float4x4 aux;

	aux.a.set(a.x, b.x, c.x, d.x);
	aux.b.set(a.y, b.y, c.y, d.y);
	aux.c.set(a.z, b.z, c.z, d.z);
	aux.d.set(a.w, b.w, c.w, d.w);

	return(aux);
}
