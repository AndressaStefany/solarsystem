//
// Created by vitor on 04/11/17.
//

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

void reshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const float ar= (float)w/h;
    gluPerspective(30,ar,0.1,100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glutSwapBuffers();
}


int main(int argc, char**argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutCreateWindow("SolarSys");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(1,1,1,1);
    glutMainLoop();
}