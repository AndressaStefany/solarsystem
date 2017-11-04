//
// Created by vitor on 04/11/17.
//

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

float dx=0, dy=0, last_x, last_y;

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

    glLoadIdentity();
    glTranslatef(0,0,-5);
    glRotatef(dy, 1,0,0);
    glRotatef(dx, 0,1,0);

    glPushMatrix();
    glColor3f(1,0,0);
    glutSolidCube(1);
    glPopMatrix();

    glutSwapBuffers();
}

void mouse(int butao, int estado, int x, int y)
{
    if(butao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
    {
        last_x=x;
        last_y=y;
    }
}

void motion(int x, int y)
{
    dx+= (x-last_x)*0.5;
    dy+= (y-last_y)*0.5;

    last_x= x;
    last_y= y;
}

void time(int t)
{
    glutPostRedisplay();
    glutTimerFunc(30, time, t);
}

int main(int argc, char**argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutCreateWindow("SolarSys");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutTimerFunc(30,time,0);

    glClearColor(1,1,1,1);
    glutMainLoop();
}