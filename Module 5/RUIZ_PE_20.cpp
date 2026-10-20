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

GLuint shipVBO,colorVBO,groundVBO,groundIndexVBO;
float shipX=-0.6f;

void init() {
    GLfloat ship[] = {
         0,0.65f,0, -0.2f,0.3f,0, 0.2f,0.3f,0
    };
    GLfloat colors[] = {
        1,0,0, 0,1,0, 0,0,1
    };
    GLfloat ground[] = {
        -1,-0.65f,0, 1,-0.65f,0,
         1,-1,0, -1,-1,0
    };
    
    GLubyte indices[]={0,1,2,0,2,3};

    glGenBuffers(1,&shipVBO);
    glBindBuffer(GL_ARRAY_BUFFER,shipVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(ship),ship,GL_DYNAMIC_DRAW);

    glGenBuffers(1,&colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER,colorVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_STATIC_DRAW);

    glGenBuffers(1,&groundVBO);
    glBindBuffer(GL_ARRAY_BUFFER,groundVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(ground),ground,GL_STATIC_DRAW);

    glGenBuffers(1,&groundIndexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,groundIndexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);

    // Draw the indexed ground.
    glColor3f(0.2f,0.7f,0.2f);
    glBindBuffer(GL_ARRAY_BUFFER,groundVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,groundIndexVBO);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_BYTE,0);

    // Draw the moving ship 
    glBindBuffer(GL_ARRAY_BUFFER,shipVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glVertexPointer(3,GL_FLOAT,0,0);

    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,colorVBO);
    glColorPointer(3,GL_FLOAT,0,0);

    glBindBuffer(GL_ARRAY_BUFFER,shipVBO);
    glDrawArrays(GL_TRIANGLES,0,3);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glFlush();
}

void timer(int value) {
    shipX+=0.1f;
    if(shipX>0.7f) shipX=-0.7f;

    glBindBuffer(GL_ARRAY_BUFFER,shipVBO);
    GLfloat* data=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);

    if(data) {
        data[0]=shipX;
        data[3]=shipX-0.2f;
        data[6]=shipX+0.2f;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glutPostRedisplay();
    glutTimerFunc(1000,timer,0);
}

void keyboard(unsigned char key,int x,int y) {
    if(key==27) {
        glDeleteBuffers(1,&shipVBO);
        glDeleteBuffers(1,&colorVBO);
        glDeleteBuffers(1,&groundVBO);
        glDeleteBuffers(1,&groundIndexVBO);
        exit(0);
    }
}

int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Ruiz_Q20");
    
#ifndef __APPLE__
    if(glewInit()!=GLEW_OK) return 1;
#endif

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000,timer,0);
    glutMainLoop();
    return 0;
}