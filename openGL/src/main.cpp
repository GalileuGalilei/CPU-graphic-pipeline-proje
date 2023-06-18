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
   mesh->transform = mesh->transform * rotation;
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
    mesh->GenerateCube();

    aux.GeneratePerpectiveMatrix(200, 100);
    mesh->transform = mesh->transform * aux;

    aux.GenerateTranslationMatrix(250, 250, -150);
    mesh->transform = mesh->transform * aux;

    aux.GenerateScaleMatrix(50);
    mesh->transform = mesh->transform * aux;

    aux.GenerateRotationMatrix(Vector3(1, 1, 1), 0.01);
    rotation = rotation * aux;

   CV::init(&screenWidth, &screenHeight, "Cube (by now...)");
   CV::run();
}
