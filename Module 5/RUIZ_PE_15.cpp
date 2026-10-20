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
float offsetY=0.0f;
float direction=0.02f;

void init() {
    GLfloat vertices[] = {
        -0.3f,-0.2f,0, 0.3f,-0.2f,0,
         0.3f, 0.2f,0,-0.3f, 0.2f,0
    };

    glGenBuffers(1,&VBOid);
    glBindBuffer(GL_ARRAY_BUFFER,VBOid);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void timer(int value) {
    offsetY+=direction;

    if(offsetY>0.5f || offsetY<-0.5f)
        direction=-direction;

    glBindBuffer(GL_ARRAY_BUFFER,VBOid);
    GLfloat* data=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);

    if(data) {
        data[1]=-0.2f+offsetY;
        data[4]=-0.2f+offsetY;
        data[7]= 0.2f+offsetY;
        data[10]=0.2f+offsetY;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glutPostRedisplay();
    glutTimerFunc(30,timer,0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0.7f,1);

    glBindBuffer(GL_ARRAY_BUFFER,VBOid);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_QUADS,0,4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glFlush();
}

int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Ruiz_Q15");
    
#ifndef __APPLE__
    if(glewInit()!=GLEW_OK) return 1;
#endif

    init();
    glutDisplayFunc(display);
    glutTimerFunc(30,timer,0);
    glutMainLoop();
    return 0;
}