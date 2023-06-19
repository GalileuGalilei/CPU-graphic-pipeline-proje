#pragma once
#include "Vectors.h"
#include <vector>

class ObjLoader
{
public:
	std::vector<Vector3> vertices;
	std::vector<int> triangles; // 3 indices per triangle

	ObjLoader();
	~ObjLoader();
	void Load(const char* filename);
	Vector3* GetVertices();
	int* GetTriangles();
};

