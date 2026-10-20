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

GLuint sunVBO,groundVBO,groundIndexVBO,treeVBO;

void init() {
    GLfloat sun[] = {
        0.55f,0.55f,0,
        0.55f,0.85f,0,
        0.85f,0.55f,0,
        0.55f,0.25f,0,
        0.25f,0.55f,0
    };

    GLfloat ground[] = {
        -1,-0.6f,0, 1,-0.6f,0,
         1,-1,0, -1,-1,0
    };
    GLubyte groundIndices[]={0,1,2,0,2,3};

    GLfloat tree[] = {
        -0.65f,-0.6f,0, -0.45f,-0.6f,0,
        -0.45f,0.0f,0, -0.65f,0.0f,0,
        -0.85f,0.0f,0, -0.25f,0.0f,0,
        -0.55f,0.55f,0
    };

    glGenBuffers(1,&sunVBO);
    glBindBuffer(GL_ARRAY_BUFFER,sunVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(sun),sun,GL_STATIC_DRAW);

    glGenBuffers(1,&groundVBO);
    glBindBuffer(GL_ARRAY_BUFFER,groundVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(ground),ground,GL_STATIC_DRAW);

    glGenBuffers(1,&groundIndexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,groundIndexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(groundIndices),
                 groundIndices,GL_STATIC_DRAW);

    glGenBuffers(1,&treeVBO);
    glBindBuffer(GL_ARRAY_BUFFER,treeVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(tree),tree,GL_STATIC_DRAW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColor3f(0.2f,0.7f,0.2f);
    glBindBuffer(GL_ARRAY_BUFFER,groundVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,groundIndexVBO);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_BYTE,0);

    glColor3f(0.5f,0.25f,0.05f);
    glBindBuffer(GL_ARRAY_BUFFER,treeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_QUADS,0,4);
    glColor3f(0,0.7f,0);
    glDrawArrays(GL_TRIANGLES,4,3);

    glColor3f(1,0.8f,0);
    glBindBuffer(GL_ARRAY_BUFFER,sunVBO);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLE_FAN,0,5);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glFlush();
}

int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Ruiz_Q16");
    
#ifndef __APPLE__
    if(glewInit()!=GLEW_OK) return 1;
#endif

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}