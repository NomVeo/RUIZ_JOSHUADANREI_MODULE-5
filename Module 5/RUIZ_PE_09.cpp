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

GLuint posVBO, colorVBO;

void init() {
    GLfloat positions[] = {
         0,0.7f,0, -0.6f,-0.5f,0, 0.6f,-0.5f,0
    };
    GLfloat colors[] = {
        1,0,0, 0,1,0, 0,0,1
    };

    glGenBuffers(1,&posVBO);
    glBindBuffer(GL_ARRAY_BUFFER,posVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(positions),positions,GL_STATIC_DRAW);

    glGenBuffers(1,&colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER,colorVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_STATIC_DRAW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER,posVBO);
    glVertexPointer(3,GL_FLOAT,0,0);

    glBindBuffer(GL_ARRAY_BUFFER,colorVBO);
    glColorPointer(3,GL_FLOAT,0,0);

    glDrawArrays(GL_TRIANGLES,0,3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glFlush();
}

int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Ruiz_Q09");
    
#ifndef __APPLE__
    if(glewInit()!=GLEW_OK) return 1;
#endif

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}