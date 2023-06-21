#pragma once
#include "Vectors.h"
#include "Matrices.h"
#include "ObjLoader.h"
#include "gl_canvas2d.h"


struct Triangle
{
	int a, b, c;//indices

	Triangle(int a, int b, int c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}
};

struct Vertex
{
	Vector4 position;
	Vector4 normal;
};

class Mesh
{
private:
	static int** zBuffer;
	static Vector3 lightSource;
	static int screenWidth, screenHeight;

	Vertex Interpolate(Vertex& a, Vertex& b, Vertex& c, float u, float v);

	//vertex shader equivalent
	void DrawTriangle(Vertex a, Vertex b, Vertex c);

	//fragment shader equivalent
	void DrawPixel(Vertex& interpolated);

public:

	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;
	Vector3 color; //cor do objeto
	Float4x4 transform; //transformacao do objeto

	void Load(const char* filename);

	void Draw();

	static void SetScreen(int screenWidth, int screenHeight);
	static void SetLightSource(Vector3 lightSource);
	static void resetZBuffer();

	template <typename T> T lerp(T a, T b, float t)
	{
		if (t > 1 || t < 0)
		{
			printf("ERRO DE LERP");
			return a;
		}
		return a + (b - a) * t;
	}
};

