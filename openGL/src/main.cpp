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
    CV::color(0, 0, 0);
    CV::rectFill(0, 0, screenWidth, screenHeight);
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
    Mesh::SetLightSource(Vector3(1, 1, 1));
    mesh->Load("monkey.obj");
    mesh->color = Vector3(1, 1, 1);

    aux.GeneratePerpectiveMatrix(200, 100);
    mesh->transform = mesh->transform * aux;

    aux.GenerateTranslationMatrix(200, 250, -250);
    mesh->transform = mesh->transform * aux;

    aux.GenerateScaleMatrix(100);
    mesh->transform = mesh->transform * aux;

    aux.GenerateRotationMatrix(Vector3(0, 1, -0.5), 0.1);
    rotation = aux;
    mesh->transform = mesh->transform * aux;

   CV::init(&screenWidth, &screenHeight, "simple obj");
   CV::run();
}
