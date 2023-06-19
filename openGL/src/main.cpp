#define _CRT_SECURE_NO_WARNINGS

#include <GL/glut.h>
#include <GL/freeglut_ext.h> 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"

#include "Mesh.h"

Mesh* mesh = NULL;
Float4x4 rotation;

int screenWidth = 500;
int screenHeight = 500;

void render()
{
   mesh->Draw();  
   Mesh::resetZBuffer();
}

void keyboard(int key){}

void keyboardUp(int key){}

void mouse(int button, int state, int wheel, int direction, int x, int y) {}

int main(void)
{
    mesh = new Mesh();
    Float4x4 aux;

    Mesh::SetScreen(screenWidth, screenHeight);
    mesh->Load("piston_gas_engine.obj");

    aux.GeneratePerpectiveMatrix(180, 100);
    mesh->transform = mesh->transform * aux;

    aux.GenerateTranslationMatrix(400, 250, -200);
    mesh->transform = mesh->transform * aux;

    aux.GenerateScaleMatrix(20);
    mesh->transform = mesh->transform * aux;

    aux.GenerateRotationMatrix(Vector3(0, 1, 0), 3.1415 / 2);
    mesh->transform = mesh->transform * aux;

   CV::init(&screenWidth, &screenHeight, "simple obj");
   CV::run();
}
