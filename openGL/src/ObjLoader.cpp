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
			fscanf(file, "%i %i %i\n", 
				&vertexIndex[0], 
				&vertexIndex[1], 
				&vertexIndex[2]);
			triangles.push_back(vertexIndex[0] - 1);
			triangles.push_back(vertexIndex[1] - 1);
			triangles.push_back(vertexIndex[2] - 1);
		}
	}
	fclose(file);
}


Vector3* ObjLoader::GetVertices()
{
	return vertices.data();
}

int* ObjLoader::GetTriangles()
{
	return triangles.data();
}