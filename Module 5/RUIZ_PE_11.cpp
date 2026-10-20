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
bool edited=false;

void init() {
    GLfloat vertices[] = {
         0,0.3f,0, -0.6f,-0.5f,0, 0.6f,-0.5f,0
    };

    glGenBuffers(1,&VBOid);
    glBindBuffer(GL_ARRAY_BUFFER,VBOid);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_DYNAMIC_DRAW);


    GLfloat* data=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);
    if(data && !edited) {
        data[1]+=0.4f;
        edited=true;
    }
    
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,1,0);

    glBindBuffer(GL_ARRAY_BUFFER,VBOid);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLES,0,3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glFlush();
}

int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Ruiz_Q11");

#ifndef __APPLE__
    if(glewInit()!=GLEW_OK) return 1;
#endif

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}