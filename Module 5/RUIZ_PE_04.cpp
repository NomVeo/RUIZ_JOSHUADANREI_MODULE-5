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

GLuint VBOid;
bool cleaned = false;

void init() {
    GLfloat vertices[] = {
         0,  0.7f, 0,
        -0.6f, -0.5f, 0,
         0.6f, -0.5f, 0
    };

    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void cleanup() {
    if (cleaned) return;

    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &VBOid);

    cleaned = true;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        cleanup();
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);

    glutCreateWindow("Ruiz_Q04");

#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}