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

GLuint VBOid,indexVBO;

void init() {
    GLfloat data[] = {
         0,0.7f,0, 1,0,0,
         0.6f,0.35f,0, 0,1,0,
         0.6f,-0.35f,0, 0,0,1,
         0,-0.7f,0, 1,1,0,
        -0.6f,-0.35f,0, 1,0,1,
        -0.6f,0.35f,0, 0,1,1
    };
    GLubyte indices[]={0,1,2,3,4,5};

    glGenBuffers(1,&VBOid);
    glBindBuffer(GL_ARRAY_BUFFER,VBOid);
    glBufferData(GL_ARRAY_BUFFER,sizeof(data),data,GL_STATIC_DRAW);

    glGenBuffers(1,&indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),
                 indices,GL_STATIC_DRAW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER,VBOid);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexVBO);

    GLsizei stride=6*sizeof(GLfloat);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3,GL_FLOAT,stride,(void*)0);
    glColorPointer(3,GL_FLOAT,stride,(void*)(3*sizeof(GLfloat)));
    glDrawElements(GL_POLYGON,6,GL_UNSIGNED_BYTE,0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glFlush();
}

int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Ruiz_Q18");
    
#ifndef __APPLE__
    if(glewInit()!=GLEW_OK) return 1;
#endif

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}