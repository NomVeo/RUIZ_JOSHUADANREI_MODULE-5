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

void init() {
    GLfloat vertices[30*2*3];

    for(int i=0;i<30;i++) {
        float angle=i*2.0f*3.14159265f/30.0f;
        float x=cosf(angle);
        float y=sinf(angle);

        float inner=0.55f;
        float outer=0.75f;

        int j=i*6;
        vertices[j]=inner*x;
        vertices[j+1]=inner*y;
        vertices[j+2]=0;

        vertices[j+3]=outer*x;
        vertices[j+4]=outer*y;
        vertices[j+5]=0;
    }

    glGenBuffers(1,&VBOid);
    glBindBuffer(GL_ARRAY_BUFFER,VBOid);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),
                 vertices,GL_STATIC_DRAW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,1,1);
    glLineWidth(3);

    glBindBuffer(GL_ARRAY_BUFFER,VBOid);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_LINES,0,60);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glFlush();
}

int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Ruiz_Q17");
    
#ifndef __APPLE__
    if(glewInit()!=GLEW_OK) return 1;
#endif

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}