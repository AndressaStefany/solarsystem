//
// Created by vitor on 04/11/17.
//

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <chrono>
#include <map>

#include "algebra.h"
#include "loading.h"
#include "camera.h"
#include "planet.h"
#include "ship.h"
#include "sky.h"
#include "interface.h"

using namespace std;
using namespace chrono;

int fps= 0;
char keys[255];
map<int,bool> spkeys;

Sky *ceu;
Ship *nave;
Planet *sun, *mercury, *venus, *earth, *mars, *jupiter, *saturn, *uranus, *neptune;
Camera *cam;
Interface *interface;

void reshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const float ar= (float)w/h;
    gluPerspective(30,ar,0.1,10000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Camera
	glLoadIdentity();

    glTranslated(0,0,-10);
	//interface->debugPoints();
    glDisable(GL_LIGHTING);
    interface->displayText(-3,2,1,0,0,("FPS "+to_string(fps)).c_str());
    glEnable(GL_LIGHTING);
//	interface->drawBox(1, 1, 255, 255, 255);	//VER
//    cam->follow(nave->getPos(), nave->getAng());
    cam->posiciona();

    GLfloat light_position[] = { 0, 0, 0, 1 }, light_ambient[]= {200.0,200.0,200.0,200};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_ambient);

    // Nave
//    nave->draw();	//Frente da nave

    // Ceu
    ceu->draw(vec3(0,0,0));

    // Referencia
//    glDisable(GL_LIGHTING);
//    glPushMatrix();
//    glColor3f(0,1,0);
//    glBegin(GL_LINES);
//    glVertex3f(0, 0, -100);
//    glVertex3f(0, 0, 100);
//    glVertex3f(0, -100, 0);
//    glVertex3f(0, 100, 0);
//    glVertex3f(-100, 0, 0);
//    glVertex3f(100, 0, 0);
//    for(int i=-10; i<=10; i++)
//    {
//        glVertex3f(i, 0, -10);
//        glVertex3f(i, 0, 10);
//
//        glVertex3f(10, 0, i);
//        glVertex3f(-10, 0, i);
//    }
//    glEnd();
//    glPopMatrix();
//    glEnable(GL_LIGHTING);

    // Planetas
    sun->draw();
    mercury->draw();
    venus->draw();
    earth->draw();
    mars->draw();
    jupiter->draw();
    saturn->draw();
    uranus->draw();
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
//    static int cont= 0;
//    static auto last_time= high_resolution_clock::now();
//    static double total=0, delta_time= 0;
//    delta_time= duration_cast<microseconds>(high_resolution_clock::now()-last_time).count();
//    last_time= high_resolution_clock::now();
//    total+=delta_time;
//    cont++;
//    if(total>1E6){
//        fps= cont;
//        total=cont=0;
//    }
//    delta_time/=1E6;
//
//    nave->update(delta_time);
//    cam->update(delta_time);
////    sun->update(delta_time);
//    mercury->update(delta_time);
//    venus->update(delta_time);
//    earth->update(delta_time);
//    mars->update(delta_time);
//    jupiter->update(delta_time);
//    saturn->update(delta_time);
//    uranus->update(delta_time);
//    neptune->update(delta_time);
//    glutPostRedisplay();
//    glutTimerFunc(30, time, t);
}

void idle()
{
    static int cont= 0;
    static auto last_time= high_resolution_clock::now();
    static double total=0, delta_time= 0;
    delta_time= duration_cast<microseconds>(high_resolution_clock::now()-last_time).count();
    last_time= high_resolution_clock::now();
    total+=delta_time;
    cont++;
    if(total>1E6){
        fps= cont;
        total=cont=0;
    }
    delta_time/=1E6;

    nave->update(delta_time);
    cam->update(delta_time);
    sun->update(delta_time);
    mercury->update(delta_time);
    venus->update(delta_time);
    earth->update(delta_time);
    mars->update(delta_time);
    jupiter->update(delta_time);
    saturn->update(delta_time);
    uranus->update(delta_time);
    neptune->update(delta_time);
    glutPostRedisplay();
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
    glutIdleFunc(idle);
    glutTimerFunc(30,time,0);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHT0);

//    glEnable(GL_LIGHT1);
//    glEnable(GL_LIGHT2);
//    glEnable(GL_LIGHT3);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_SRC_ALPHA,0);
    glEnable(GL_ALPHA_TEST);

    glEnable(GL_MULTISAMPLE_ARB);

    try {
        float k= 500;
        cam = new Camera(vec3(-700,0,0));
        nave = new Ship("objetos/nave", vec3(0,0,500), vec3(0,0,0));
        ceu = new Sky("objetos/sky");
        sun = new Planet("objetos/planets/sun", vec3(0,0,0), 0, 0, 0, 0, 0, 0);
        mercury  = new Planet("objetos/planets/mercury",
                              vec3(0,0,0), 400*1, 400*700/460.0, 88, 59, 0, 90);
        venus    = new Planet("objetos/planets/venus",
                              vec3(0,0,0), 1000*1, 1000*1009/1007.0, 225, 243, 0, 90);
        earth    = new Planet("objetos/planets/earth",
                              vec3(0,0,0), 1500*1, 1500*1520/1470.0, 365, 1, 0, 90);
        mars     = new Planet("objetos/planets/mars",
                              vec3(0,0,0), 2000*1, 2000*2490/2050.0, 687, 1, 0, 90);
        jupiter  = new Planet("objetos/planets/jupiter",
                              vec3(0,0,0), 2500*1, 2500*8170/7410.0, 4329/3.0, 0.4, 0, 90);
        saturn   = new Planet("objetos/planets/saturn",
                              vec3(0,0,0), 3000*1, 3000*15100/13500.0, 10751/4.5, 0.43, 0, 90);
        uranus   = new Planet("objetos/planets/uranus",
                              vec3(0,0,0), 3500*1, 3500*30000/27500.0, 30660/7.9, 0.76, 0, 90);
        neptune  = new Planet("objetos/planets/neptune",
                              vec3(0,0,0), 4000*1, 4000*45500/44500.0, 59860/11.125, 6.39, 0, 90);
        interface = new Interface();
    } catch(const char* erro)
    {
        cerr << erro << endl;
    }

    glClearColor(0,0,0,0);
    glutMainLoop();
}
