//
// Created by vitor on 04/11/17.
//

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <map>

#include "algebra.h"
#include "loading.h"
#include "camera.h"
#include "planet.h"
#include "ship.h"
#include "sky.h"
#include "interface.h"

using namespace std;

char keys[255];
map<int,bool> spkeys;

Sky *ceu;
Ship *nave;
Planet *sun, *venus, *terra, *jupiter, *saturn, *neptune;
Camera *cam;
Interface *interface;

void reshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const float ar= (float)w/h;
    gluPerspective(30,ar,0.1,1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Camera
    //cam->follow(nave->getPos());
	glLoadIdentity();
    glTranslated(0,0,-10);
	//interface->debugPoints();
	interface->drawBox(1, 1, 255, 255, 255);	//VER
    cam->posiciona();

    // Nave
    nave->draw();	//Frente da nave

    // Ceu
    ceu->draw(nave->getPos());

    // Referencia
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, -100);
    glVertex3f(0, 0, 100);
    glVertex3f(0, -100, 0);
    glVertex3f(0, 100, 0);
    glVertex3f(-100, 0, 0);
    glVertex3f(100, 0, 0);
    for(int i=-10; i<=10; i++)
    {
        glVertex3f(i, 0, -10);
        glVertex3f(i, 0, 10);

        glVertex3f(10, 0, i);
        glVertex3f(-10, 0, i);
    }
    glEnd();
    glPopMatrix();
	
	glEnable(GL_LIGHTING);
	
    // Planetas
    venus->draw();
    sun->draw();
    terra->draw();
    jupiter->draw();
    saturn->draw();
    neptune->draw();
    
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    cam->mouse(button, state, x, y);
}

void motion(int x, int y)
{
    cam->motion(x, y);
}

void keyboardUp(unsigned char key, int x, int y)
{
    keys[key]= false;
}

void keyboard(unsigned char key, int x, int y)
{
    keys[key]= true;
}

void specialkeysUp(int key, int x, int y)
{
    spkeys[key]= false;
}

void specialkeys(int key, int x, int y)
{
    spkeys[key]= true;
}
void time(int t)
{
    nave->update();
    cam->update();
    glutPostRedisplay();
    glutTimerFunc(30, time, t);
}

int main(int argc, char**argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(640,480);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("SolarSys");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialUpFunc(specialkeysUp);
    glutSpecialFunc(specialkeys);
    glutTimerFunc(30,time,0);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_SRC_ALPHA,0);
    glEnable(GL_ALPHA_TEST);

    glEnable(GL_MULTISAMPLE_ARB);

    cam = new Camera(vec3(0,0,0));
    nave = new Ship("objetos/nave", vec3(10,0,0), vec3(0,0,0));
    ceu = new Sky("objetos/sky");
    sun = new Planet("objetos/planetas/sun", vec3(0,0,0), 0, 0, 0, 0, 0);
    venus = new Planet("objetos/planetas/venus", vec3(0,0,0), 9, 6, 0.1, 120, 67);
    terra = new Planet("objetos/planetas/terra", vec3(0,0,0), 12, 10, 0.1, 50, 80);
    jupiter = new Planet("objetos/planetas/jupiter", vec3(0,0,0), 15, 15, 0.1, 80, 30);
    saturn = new Planet("objetos/planetas/saturn", vec3(0,0,0), 18, 10, 0.1, -30, -120);
    neptune = new Planet("objetos/planetas/neptune", vec3(0,0,0), 20, 25, 0.1, 20,-50);
	interface = new Interface();

    glClearColor(0,0,0,0);
    glutMainLoop();
}
