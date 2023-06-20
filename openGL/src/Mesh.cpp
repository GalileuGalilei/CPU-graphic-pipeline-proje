#include "Mesh.h"
#include <algorithm>

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

Vector3 Mesh::lightSource = Vector3(0, 0, 1);

void Mesh::SetLightSource(Vector3 lightSource)
{
	Mesh::lightSource = lightSource;
}

void Mesh::resetZBuffer()
{
	for (int i = 0; i < Mesh::screenWidth; i++)
	{
		for (int j = 0; j < Mesh::screenHeight; j++)
		{
			zBuffer[i][j] = -99999;
			int a =2;
		}
	}
}

void Mesh::Load(const char* filename)
{
	ObjLoader loader;
	loader.Load(filename);

	for (int i = 0; i < loader.vertices.size(); i++)
	{
		Vertex v;
		v.position = Vector4(loader.vertices[i].x, loader.vertices[i].y, loader.vertices[i].z, 1);
		v.normal = Vector4(loader.normals[i].x, loader.normals[i].y, loader.normals[i].z, 0);

		vertices.push_back(v);
	}
	for (int i = 0; i < loader.triangles.size(); i += 3)
	{
		triangles.push_back(Triangle(loader.triangles[i], loader.triangles[i + 1], loader.triangles[i + 2]));
	}
}

Vertex Mesh::Interpolate(Vertex& a, Vertex& b, float t)
{
	Vertex v;
	v.position = lerp(a.position, b.position, t);
	v.normal = lerp(a.normal, b.normal, t);
	
	return v;
}

void Mesh::DrawPixel(Vertex& i)
{
	int x = (int)i.position.x;
	int y = (int)i.position.y;

	Vector3 lightDir = lightSource - i.position;
	lightDir.Normalize();
	Vector3 normal = i.normal;
	normal.Normalize();
	float intensity = std::max(normal.Dot(lightDir), 0.0f);
	//CV::color(color.x * intensity, color.y * intensity, color.z * intensity);
	//CV::color(1, 1, 1);
	glVertex2d(x, y);
}

void Mesh::DrawTriangle(Vertex a, Vertex b, Vertex c)
{
	glBegin(GL_POINTS);

	//ordena os pontos do menor para o maior y.
	if(a.position.y > b.position.y) std::swap(a, b);
	if(a.position.y > c.position.y) std::swap(a, c);
	if(b.position.y > c.position.y) std::swap(b, c);

	Vector3 p1 = a.position;
	Vector3 p2 = b.position;
	Vector3 p3 = c.position;

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

		int horizontalSegment = B.x - A.x + 1;

		for (int x = A.x; x < B.x; x++)
		{
			if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight)
			{
				continue;
			}

			float gama = (float)(x - (int)A.x) / horizontalSegment;

			Vertex v1 = Interpolate(a, c, alpha);
			Vertex v2 = Interpolate(a, b, beta);
			Vertex v3 = Interpolate(v1, v2, gama);

			if (zBuffer[x][y] < v3.position.z)
			{
				v3.position.x = x;
				v3.position.y = y;
				DrawPixel(v3);
				zBuffer[x][y] = v3.position.z;
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

		int horizontalSegment = B.x - A.x + 1;

		for (int x = A.x; x < B.x; x++)
		{
			if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight)
			{
				continue;
			}

			float gama = (float)(x - (int)A.x) / horizontalSegment;

			Vertex v1 = Interpolate(a, c, alpha);
			Vertex v2 = Interpolate(b, c, beta);
			Vertex v3 = Interpolate(v1, v2, gama);

			if (zBuffer[x][y] < v3.position.z)
			{
				v3.position.x = x;
				v3.position.y = y;
				DrawPixel(v3);
				zBuffer[x][y] = v3.position.z;
			}
		}
	}

	glEnd();
}

void Mesh::Draw()
{
	Vector4 center = Vector4((float)screenWidth / 2, (float)screenHeight / 2, 0, 0);

	CV::color(0, 0, 0);
	for(int i = 0; i < triangles.size(); i++)
	{
		Triangle t = triangles[i];
		Vertex v1;
		Vertex v2;
		Vertex v3;

		Vector4 a = transform * vertices[t.a].position - center;
		Vector4 b = transform * vertices[t.b].position - center;
		Vector4 c = transform * vertices[t.c].position - center;

		//não funciona com escalas não homogeneas
		v1.normal = transform * vertices[t.a].normal / a.w;
		v2.normal = transform * vertices[t.b].normal / b.w;
		v3.normal = transform * vertices[t.c].normal / c.w;

		v1.position = Vector4(a.x / a.w, a.y / a.w, a.z, a.w) + center;
		v2.position = Vector4(b.x / b.w, b.y / b.w, b.z, b.w) + center;
		v3.position = Vector4(c.x / c.w, c.y / c.w, c.z, c.w) + center;

		float color = (float)i / triangles.size();
		CV::color(color, color, color);
		DrawTriangle(v1, v2, v3);
	}
}
