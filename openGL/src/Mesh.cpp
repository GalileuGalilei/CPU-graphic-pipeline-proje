#include "Mesh.h"
#include <algorithm>

Vector3 lerp(Vector3 a, Vector3 b, float t)
{
	return a + (b - a) * t;
}

int** Mesh::zBuffer = NULL;

int Mesh::screenWidth = 0;
int Mesh::screenHeight = 0;

void Mesh::SetScreen(int screenWidth, int screenHeight)
{
	Mesh::screenWidth = screenWidth;
	Mesh::screenHeight = screenHeight;

	if (zBuffer == NULL)
	{
		zBuffer = new int*[screenWidth];
		for (int i = 0; i < screenWidth; i++)
		{
			zBuffer[i] = new int[screenHeight];
		}
	}

	resetZBuffer();
}	

void Mesh::resetZBuffer()
{
	for (int i = 0; i < Mesh::screenWidth; i++)
	{
		for (int j = 0; j < Mesh::screenHeight; j++)
		{
			zBuffer[i][j] = 0;
		}
	}
}

void Mesh::GenerateCube()
{
	vertices.push_back(Vector4(-0.5f, -0.5f, -0.5f, 1));
	vertices.push_back(Vector4(-0.5f, 0.5f, -0.5f, 1));
	vertices.push_back(Vector4(0.5f, 0.5f, -0.5f, 1));
	vertices.push_back(Vector4(0.5f, -0.5f, -0.5f, 1));
	vertices.push_back(Vector4(-0.5f, -0.5f, 0.5f, 1));
	vertices.push_back(Vector4(-0.5f, 0.5f, 0.5f, 1));
	vertices.push_back(Vector4(0.5f, 0.5f, 0.5f, 1));
	vertices.push_back(Vector4(0.5f, -0.5f, 0.5f, 1));

	triangles.push_back(Triangle(0, 1, 2));
	triangles.push_back(Triangle(0, 2, 3));
	triangles.push_back(Triangle(4, 6, 5));
	triangles.push_back(Triangle(4, 7, 6));
	triangles.push_back(Triangle(0, 4, 1));
	triangles.push_back(Triangle(1, 4, 5));
	triangles.push_back(Triangle(1, 5, 2));
	triangles.push_back(Triangle(2, 5, 6));
	triangles.push_back(Triangle(2, 6, 3));
	triangles.push_back(Triangle(3, 6, 7));
	triangles.push_back(Triangle(3, 7, 0));
	triangles.push_back(Triangle(0, 7, 4));
}

void Mesh::Load(const char* filename)
{
	ObjLoader loader;
	loader.Load(filename);

	for (int i = 0; i < loader.vertices.size(); i++)
	{
		vertices.push_back(Vector4(loader.vertices[i].x, loader.vertices[i].y, loader.vertices[i].z, 1));
	}
	for (int i = 0; i < loader.triangles.size(); i += 3)
	{
		triangles.push_back(Triangle(loader.triangles[i], loader.triangles[i + 1], loader.triangles[i + 2]));
	}
}

void Mesh::DrawTriangle(Vector3 p1, Vector3 p2, Vector3 p3)
{
	CV::color(0, 0, 0);
	glBegin(GL_POINTS);
	//ordena os pontos do menor para o maior y.
	if (p1.y > p2.y) std::swap(p1, p2);
	if (p1.y > p3.y) std::swap(p1, p3);
	if (p2.y > p3.y) std::swap(p2, p3);

	int totalHeight = (int)p3.y - (int)p1.y + 1;
	int segmentHeight = (int)p2.y - (int)p1.y + 1;
	Vector3 dirA = p3 - p1;
	Vector3 dirB = p2 - p1;

	//para cada linha de p1 a p2
	for (int y = p1.y; y < p2.y; y++)
	{
		float alpha = (float)(y - (int)p1.y) / totalHeight;
		float beta = (float)(y - (int)p1.y) / segmentHeight;

		Vector3 A = dirA * alpha + p1;
		Vector3 B = dirB * beta + p1;
		if (A.x > B.x) std::swap(A, B);

		int horizontalSegment = B.x - A.x;

		for (int x = A.x; x < B.x; x++)
		{
			if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight)
			{
				continue;
			}

			int gama = (float)(x - (int)A.x) / horizontalSegment;
			Vector3 C = lerp(A, B, gama);

			if (zBuffer[x][y] > C.z)
			{
				glVertex2i(x, y);
				zBuffer[x][y] = C.z;
			}
		}
	}

	segmentHeight = (int)p3.y - (int)p2.y + 1;
	dirA = p3 - p1;
	dirB = p3 - p2;

	//para cada linha de p2 a p3
	for (int y = p2.y; y < p3.y; y++)
	{
		float alpha = (float)(y - (int)p1.y) / totalHeight;
		float beta = (float)(y - (int)p2.y) / segmentHeight;

		Vector3 A = dirA * alpha + p1;
		Vector3 B = dirB * beta + p2;
		if (A.x > B.x) std::swap(A, B);

		int horizontalSegment = B.x - A.x;

		for (int x = A.x; x < B.x; x++)
		{
			if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight)
			{
				continue;
			}

			float gama = (float)(x - (int)A.x) / horizontalSegment;
			Vector3 C = lerp(A, B, gama);

			if (zBuffer[x][y] > C.z)
			{
				glVertex2i(x, y);
				zBuffer[x][y] = C.z;
			}
		}
	}

	glEnd();
}

void Mesh::Draw()
{
	Vector4 center = Vector4((float)screenWidth / 2, (float)screenHeight / 2, 0, 0);

	CV::color(0, 0, 0);
	for (Triangle t : triangles)
	{
		Vector4 a = transform * vertices[t.a] - center;
		Vector4 b = transform * vertices[t.b] - center;
		Vector4 c = transform * vertices[t.c] - center;

		Vector3 p1 = Vector3(a.x / a.w, a.y / a.w, a.z) + center;
		Vector3 p2 = Vector3(b.x / b.w, b.y / b.w, b.z) + center;
		Vector3 p3 = Vector3(c.x / c.w, c.y / c.w, c.z) + center;

		DrawTriangle(p1, p2, p3);
	}
}
