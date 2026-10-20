#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

GLuint leftVBO, rightVBO;

void init() {
    GLfloat left[] = {
        -0.6f, 0.5f, 0,
        -0.9f, -0.3f, 0,
        -0.3f, -0.3f, 0
    };

    GLfloat right[] = {
         0.6f, 0.5f, 0,
         0.3f, -0.3f, 0,
         0.9f, -0.3f, 0
    };

    glGenBuffers(1, &leftVBO);
    glBindBuffer(GL_ARRAY_BUFFER, leftVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(left), left, GL_STATIC_DRAW);

    glGenBuffers(1, &rightVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(right), right, GL_STATIC_DRAW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColor3f(1, 0.3f, 0);
    glBindBuffer(GL_ARRAY_BUFFER, leftVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glColor3f(0, 0.5f, 1);
    glBindBuffer(GL_ARRAY_BUFFER, rightVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    
    glutCreateWindow("Ruiz_Q05");

#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}