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

Vertex Mesh::Interpolate(Vertex& a, Vertex& b, Vertex& c, float u, float v)
{
	Vertex i;

	i.position = a.position * u + b.position * v + c.position * (1 - u - v);
	i.normal = a.normal * u + b.normal * v + c.normal * (1 - u - v);
	
	return i;
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
	CV::color(color.x * intensity, color.y * intensity, color.z * intensity);
	//CV::color(1, 1, 1);
	glVertex2d(x, y);
}

Vector3 Barycentric(Vector4& a, Vector4& b, Vector4& c, Vector2& point)
{
	Vector3 v0 = Vector3(c.x - a.x, b.x - a.x, a.x - point.x);
	Vector3 v1 = Vector3(c.y - a.y, b.y - a.y, a.y - point.y);
	Vector3 u = v0 * v1;
	if (std::abs(u.z) > 1e-2)
	{
		return Vector3(1.0f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
	}

	return Vector3(-1, 1, 1);
}

void Mesh::DrawTriangle(Vertex a, Vertex b, Vertex c)
{
	glBegin(GL_POINTS);

	//encontra a bounds box
	int minX = std::min(a.position.x, std::min(b.position.x, c.position.x));
	int maxX = std::max(a.position.x, std::max(b.position.x, c.position.x));
	int minY = std::min(a.position.y, std::min(b.position.y, c.position.y));
	int maxY = std::max(a.position.y, std::max(b.position.y, c.position.y));

	//percorre a bounds box
	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			Vector2 p = Vector2(x, y);
			Vector3 barycentric = Barycentric(a.position, b.position, c.position, p);
			if (barycentric.x < 0 || barycentric.y < 0 || barycentric.z < 0)
			{
				//fora do triangulo
				continue;
			}
			Vertex i = Interpolate(a, b, c, barycentric.x, barycentric.y);
			if (zBuffer[x][y] < i.position.z)
			{
				i.position.x = x;
				i.position.y = y;
				zBuffer[x][y] = i.position.z;
				DrawPixel(i);
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
		v1.normal = transform * vertices[t.a].normal;
		v2.normal = transform * vertices[t.b].normal;
		v3.normal = transform * vertices[t.c].normal;

		v1.position = Vector4(a.x / a.w, a.y / a.w, a.z, a.w) + center;
		v2.position = Vector4(b.x / b.w, b.y / b.w, b.z, b.w) + center;
		v3.position = Vector4(c.x / c.w, c.y / c.w, c.z, c.w) + center;

		float color = (float)i / triangles.size();
		CV::color(color, color, color);
		DrawTriangle(v1, v2, v3);
	}
}
