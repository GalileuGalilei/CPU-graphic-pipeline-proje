#include "ObjLoader.h"

ObjLoader::ObjLoader()
{

}

ObjLoader::~ObjLoader()
{

}

void ObjLoader::Load(const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("file not found\n");
		return;
	}

	while (true)
	{
		char currentStr[128];
		int res = fscanf(file, "%s", currentStr);
		if (res == EOF)
		{
			break;
		}

		if (strcmp(currentStr, "v") == 0)
		{
			Vector3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertices.push_back(vertex);
		}

		else if (strcmp(currentStr, "f") == 0)
		{
			int vertexIndex[3];
			int t; //trash

			fscanf(file, "%i//%i %i//%i %i//%i\n", &vertexIndex[0], &t, &vertexIndex[1], &t, &vertexIndex[2], &t);
			triangles.push_back(vertexIndex[0] - 1);
			triangles.push_back(vertexIndex[1] - 1);
			triangles.push_back(vertexIndex[2] - 1);
		}
	}
	fclose(file);

	CalculateNormalPerVertex();
}

void ObjLoader::CalculateNormalPerVertex()
{
	normals.resize(vertices.size());

	for (int i = 0; i < vertices.size(); i++)
	{
		Vector3 normal = Vector3(0, 0, 0);
		for (int j = 0; j < triangles.size(); j += 3)
		{
			if (triangles[j] == i || triangles[j + 1] == i || triangles[j + 2] == i)
			{
				Vector3 v1 = vertices[triangles[j + 1]] - vertices[triangles[j]];
				Vector3 v2 = vertices[triangles[j + 2]] - vertices[triangles[j]];
				normal += v1 * v2;
			}
		}
		normal.Normalize();
		normals[i] = normal;
	}
}

Vector3* ObjLoader::GetVertices()
{
	return vertices.data();
}

int* ObjLoader::GetTriangles()
{
	return triangles.data();
}