#pragma once
#include "Vectors.h"
#include "Matrices.h"
#include "gl_canvas2d.h"
#include <vector>

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

class Mesh
{
private:
	static int** zBuffer;
	static int screenWidth, screenHeight;

public:

	std::vector<Vector4> vertices;
	//std::vector<Edge> edges;
	std::vector<Triangle> triangles;
	Float4x4 transform;//transformacao do objeto
	//dps faz o resto

	void GenerateCube();

	void DrawTriangle(Vector3 a, Vector3 b, Vector3 c);

	void Draw();

	static void SetScreen(int screenWidth, int screenHeight);
	static void resetZBuffer();
};

