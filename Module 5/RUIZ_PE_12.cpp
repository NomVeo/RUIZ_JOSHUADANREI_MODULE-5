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
    GLfloat point[] = {-0.8f,0,0};
    glGenBuffers(1,&VBOid);
    glBindBuffer(GL_ARRAY_BUFFER,VBOid);
    glBufferData(GL_ARRAY_BUFFER,sizeof(point),point,GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void timer(int value) {
    glBindBuffer(GL_ARRAY_BUFFER,VBOid);
    GLfloat* data=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);
    
    if(data) {
        data[0]+=0.1f;
        if(data[0]>1.0f) data[0]=-1.0f;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glutPostRedisplay();
    glutTimerFunc(1000,timer,0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glPointSize(15);

    glBindBuffer(GL_ARRAY_BUFFER,VBOid);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_POINTS,0,1);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    glFlush();
}

int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Ruiz_Q12");

#ifndef __APPLE__
    if(glewInit()!=GLEW_OK) return 1;
#endif

    init();
    glutDisplayFunc(display);
    glutTimerFunc(1000,timer,0);
    glutMainLoop();
    return 0;
}