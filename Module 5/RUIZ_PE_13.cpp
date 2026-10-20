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

GLuint VBO1,VBO2;

void init() {
    GLfloat a[]={-0.8f,0.4f,0,-0.4f,0.4f,0,-0.6f,-0.4f,0};
    GLfloat b[]={0.4f,0.4f,0,0.8f,0.4f,0,0.6f,-0.4f,0};

    glGenBuffers(1,&VBO1);
    glBindBuffer(GL_ARRAY_BUFFER,VBO1);
    glBufferData(GL_ARRAY_BUFFER,sizeof(a),a,GL_STATIC_DRAW);

    glGenBuffers(1,&VBO2);
    glBindBuffer(GL_ARRAY_BUFFER,VBO2);
    glBufferData(GL_ARRAY_BUFFER,sizeof(b),b,GL_STATIC_DRAW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColor3f(1,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,VBO1);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLES,0,3);

    glColor3f(0,0,1);
    glBindBuffer(GL_ARRAY_BUFFER,VBO2);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLES,0,3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glFlush();
}

void monitorKeyboard(unsigned char key,int x,int y) {
    if(key==27) {
        glDeleteBuffers(1,&VBO1);
        glDeleteBuffers(1,&VBO2);
        exit(0);
    }
}

int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Ruiz_Q13");
    
#ifndef __APPLE__
    if(glewInit()!=GLEW_OK) return 1;
#endif

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);
    glutMainLoop();
    return 0;
}