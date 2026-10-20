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

GLuint posVBO,colorVBO;
int scheme=0;

void init() {
    GLfloat positions[] = {
         0,0.7f,0, -0.6f,-0.5f,0, 0.6f,-0.5f,0
    };
    GLfloat colors[] = {
        1,0,0, 1,0,0, 1,0,0
    };

    glGenBuffers(1,&posVBO);
    glBindBuffer(GL_ARRAY_BUFFER,posVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(positions),positions,GL_STATIC_DRAW);

    glGenBuffers(1,&colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER,colorVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_DYNAMIC_DRAW);
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

void keyboard(unsigned char key,int x,int y) {
    if(key=='c' || key=='C') {
        scheme=(scheme+1)%3;
        glBindBuffer(GL_ARRAY_BUFFER,colorVBO);

        GLfloat* colors=(GLfloat*)glMapBuffer(
            GL_ARRAY_BUFFER,GL_READ_WRITE);

        if(colors) {
            for(int i=0;i<3;i++) {
                if(scheme==0) {
                    colors[i*3]=1; colors[i*3+1]=0; colors[i*3+2]=0;
                } else if(scheme==1) {
                    colors[i*3]=0; colors[i*3+1]=1; colors[i*3+2]=0;
                } else {
                    colors[i*3]=0; colors[i*3+1]=0; colors[i*3+2]=1;
                }
            }
            glUnmapBuffer(GL_ARRAY_BUFFER);
        }

        glBindBuffer(GL_ARRAY_BUFFER,0);
        glutPostRedisplay();
    }

    if(key==27) {
        glDeleteBuffers(1,&posVBO);
        glDeleteBuffers(1,&colorVBO);
        exit(0);
    }
}

int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Ruiz_Q19");
    
#ifndef __APPLE__
    if(glewInit()!=GLEW_OK) return 1;
#endif

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}