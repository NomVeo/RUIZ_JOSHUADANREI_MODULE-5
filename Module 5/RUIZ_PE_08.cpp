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

GLuint VBOid, VBOindex;

void init() {
    GLfloat vertices[] = {
        -0.5f,-0.5f,0, 0.5f,-0.5f,0,
         0.5f, 0.5f,0,-0.5f, 0.5f,0
    };
    GLubyte indices[] = {0,1,2,0,2,3};

    glGenBuffers(1,&VBOid);
    glBindBuffer(GL_ARRAY_BUFFER,VBOid);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glGenBuffers(1,&VBOindex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,VBOindex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0.5f,0);

    glBindBuffer(GL_ARRAY_BUFFER,VBOid);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,VBOindex);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_BYTE,0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glFlush();
}

int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Ruiz_Q08");

#ifndef __APPLE__
    if(glewInit()!=GLEW_OK) return 1;
#endif

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}