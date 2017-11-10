//
// Created by vitor on 04/11/17.
//

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include "algebra.h"
#include "loading.h"

using namespace std;

float dx = 0, dy = 0, last_x, last_y;
float pos_x = 0, speed_x = 0;
float pos_y = 0, speed_y = 0;
float pos_z = 0, speed_z = 0;
const float max_speed = 0.1, acceleration = 0.01;
float ang_v = 0, ang_h = 0;

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
    pos_x += speed_x;
    pos_y += speed_y;
    pos_z += speed_z;
    
    glLoadIdentity();
    //glTranslatef(pos_x,pos_y,pos_z-5);	//Fazer a camera acompanhar a nave, mais ou menos
    glTranslatef(0,0,-5);
    glRotatef(dy,1,0,0);
    glRotatef(dx,0,1,0);
    glRotatef(180,1,0,0);
    
    //Nave
    glPushMatrix();
    glTranslatef(pos_x,pos_y,pos_z);
    glRotatef(ang_v,1,0,0);
    glRotatef(ang_h,0,1,0);
    glPushMatrix();
    glTranslatef(0,0,0.5);
    glColor3f(1,0,0);
    glutSolidSphere(0.1, 20, 16);	//Frente da nave
    glPopMatrix();
    glutWireCube(1);
    glPopMatrix();
    
    //Referência
    glTranslatef(0,0,10);
    glPushMatrix();
    glColor3f(1,1,0);
    glutWireSphere(0.5, 20, 16);
    glPopMatrix();
    
    glutSwapBuffers();
}

void mouse(int botao, int estado, int x, int y)
{
    last_x=x;
    last_y=y;
    if(botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
    {

    }
}

void motion(int x, int y)
{
    dx += (x-last_x)*0.3;
    dy += (y-last_y)*0.3;

    last_x = x;
    last_y = y;
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'z':
      case 'Z':
         speed_x += acceleration*sin(ang_h);
         speed_y += -acceleration*sin(ang_v);
         speed_z += (acceleration*cos(ang_v) + acceleration*cos(ang_h));
         if (speed_x > max_speed) {
             speed_x = max_speed;
         }
         if (speed_y > max_speed) {
             speed_y = max_speed;
         }
         if (speed_z > max_speed) {
             speed_z = max_speed;
         }
         break;
      case 'x':
      case 'X':
         if (speed_x >= 0) {
             speed_x -= acceleration*sin(ang_h);
         } else {
             speed_x += acceleration*sin(ang_h);
         }
         if (speed_y >= 0) {
             speed_y -= -acceleration*sin(ang_v);
         } else {
             speed_y += -acceleration*sin(ang_v);
         }
         if (speed_z >= 0) {
             speed_z -= (acceleration*cos(ang_v) + acceleration*cos(ang_h));
         } else {
             speed_z += (acceleration*cos(ang_v) + acceleration*cos(ang_h));
         }
         if (speed_x < -max_speed) {
             speed_x = -max_speed;
         }
         if (speed_y < -max_speed) {
             speed_y = -max_speed;
         }
         if (speed_z < -max_speed) {
             speed_z = -max_speed;
         }
         break;
      default:
         break;
   }
}

void specialkeys(int key, int x, int y)
{
    switch (key) {
      case GLUT_KEY_UP:
         ang_v += 1;
         if (ang_v > 90) {
             ang_v = 90;
         }
         break;
      case GLUT_KEY_DOWN:
         ang_v -= 1;
         if (ang_v < -90) {
             ang_v = -90;
         }
         break;
      case GLUT_KEY_LEFT:
         ang_h -= 1;
         if (ang_h < -90) {
             ang_h = 90;
         }
         break;
      case GLUT_KEY_RIGHT:
         ang_h += 1;
         if (ang_h > 90) {
             ang_h = 90;
         }
         break;
      default:
         break;
    }
}

void time(int t)
{
    glutPostRedisplay();
    glutTimerFunc(30, time, t);
}

void init (void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char**argv)
{
    //Loading teste("../cube.obj");
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("SolarSys");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkeys);
    glutTimerFunc(30,time,0);

    //glClearColor(0,0,0,0);
    glutMainLoop();
}
