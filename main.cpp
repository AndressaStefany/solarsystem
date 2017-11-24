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

int fps = 0;
char keys[255];
map<int,bool> spkeys;
GLfloat light_position[] = {0, 0, 0, 1}, light_ambient[]= {200.0, 200.0, 200.0, 200};
double animation_speed = 1;

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
    gluPerspective(30,ar,0.1,50000);

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
	interface->drawInterface(fps, animation_speed, nave);
	glEnable(GL_LIGHTING);
    cam->posiciona();
	//interface->drawBox(1000, 1000, 255, 255, 255);	//VER
    // Posiciona a luz
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_ambient);
    // Nave
    nave->draw();	//Frente da nave
    // Ceu
    ceu->draw(vec3(0,0,0));
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
    keys[key] = false;
}

void keyboard(unsigned char key, int x, int y)
{
    keys[key] = true;
	
	if(keys['e'])
	{
		if(animation_speed == 100.0)
			animation_speed = 1000.0;
		if(animation_speed == 50.0)
			animation_speed = 100.0;
		if(animation_speed == 20.0)
			animation_speed = 50.0;
		if(animation_speed == 10.0)
			animation_speed = 20.0;
		if(animation_speed == 5.0)
			animation_speed = 10.0;
		if(animation_speed == 2.0)
			animation_speed = 5.0;
		if(animation_speed == 1.0)
			animation_speed = 2.0;
		if(animation_speed == 0.5)
			animation_speed = 1.0;
		if(animation_speed == 0.1)
			animation_speed = 0.5;
		if(animation_speed == 0.01)
			animation_speed = 0.1;
	}
    if(keys['r'])
	{
		if(animation_speed == 0.1)
			animation_speed = 0.01;
		if(animation_speed == 0.5)
			animation_speed = 0.1;
		if(animation_speed == 1.0)
			animation_speed = 0.5;
		if(animation_speed == 2.0)
			animation_speed = 1.0;
		if(animation_speed == 5.0)
			animation_speed = 2.0;
		if(animation_speed == 10.0)
			animation_speed = 5.0;
		if(animation_speed == 20.0)
			animation_speed = 10.0;
		if(animation_speed == 50.0)
			animation_speed = 20.0;
		if(animation_speed == 100.0)
			animation_speed = 50.0;
		if(animation_speed == 1000.0)
			animation_speed = 100.0;
	}
}

void specialkeysUp(int key, int x, int y)
{
    spkeys[key] = false;
}

void specialkeys(int key, int x, int y)
{
    spkeys[key] = true;
}

void time(int t)
{
//    glutPostRedisplay();
//    glutTimerFunc(30, time, t);
}

void idle()
{
    static int cont = 0;
    static auto last_time = high_resolution_clock::now();
    static double total = 0, delta_time = 0;
    delta_time= duration_cast<microseconds>(high_resolution_clock::now()-last_time).count();
    last_time= high_resolution_clock::now();
    total+=delta_time;
    cont++;
    if(total>1E6){
        fps= cont;
        total=cont=0;
    }
    delta_time/=1E6;
    delta_time*=animation_speed;

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

    if(keys['1']) cam->setFollow(mercury, 20);
    if(keys['2']) cam->setFollow(venus, 40);
    if(keys['3']) cam->setFollow(earth, 40);
    if(keys['4']) cam->setFollow(mars, 20);
    if(keys['5']) cam->setFollow(jupiter, 160);
    if(keys['6']) cam->setFollow(saturn, 160);
    if(keys['7']) cam->setFollow(uranus, 80);
    if(keys['8']) cam->setFollow(neptune, 80);
    if(keys['f']) cam->setFree();
    if(keys['n']) cam->setFollow(nave, 10);

    //if(keys['e']) animation_speed+=delta_time;
    //if(keys['r']) animation_speed-=delta_time;
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
        cam = new Camera(vec3(-700,0,0), 0, 0);
        nave = new Ship("objetos/nave", vec3(0,0,500), vec3(0,0,0));
        ceu = new Sky("objetos/sky");
        sun = new Planet("objetos/planets/sun", vec3(0,0,0), 0, 0, 0, 0, 0, 0, 7.25);
        mercury  = new Planet("objetos/planets/mercury",
                              vec3(0,0,0), 400*1, 400*700/460.0, 88, 59, 0, 90-6.34, 0.01);
        venus    = new Planet("objetos/planets/venus",
                              vec3(0,0,0), 1000*1, 1000*1009/1007.0, 225, 243, 0, 90-2.19, 177.36);
        earth    = new Planet("objetos/planets/earth",
                              vec3(0,0,0), 1500*1, 1500*1520/1470.0, 365, 1, 0, 90-1.57, 23.44);
        mars     = new Planet("objetos/planets/mars",
                              vec3(0,0,0), 2000*1, 2000*2490/2050.0, 687, 1, 0, 90-1.67, 25.19);
        jupiter  = new Planet("objetos/planets/jupiter",
                              vec3(0,0,0), 2500*1, 2500*8170/7410.0, 4329/3.0, 0.4, 0, 90-0.32, 3.12);
        saturn   = new Planet("objetos/planets/saturn",
                              vec3(0,0,0), 3000*1, 3000*15100/13500.0, 10751/4.5, 0.43, 0, 90-0.93, 26.73);
        uranus   = new Planet("objetos/planets/uranus",
                              vec3(0,0,0), 3500*1, 3500*30000/27500.0, 30660/7.9, 0.76, 0, 90-1.02, 97.77);
        neptune  = new Planet("objetos/planets/neptune",
                              vec3(0,0,0), 4000*1, 4000*45500/44500.0, 59860/11.125, 6.39, 0, 90-0.72, 28.33);
        interface = new Interface(1,1,1);
    } catch(const char* erro)
    {
        cerr << erro << endl;
    }

    glClearColor(0,0,0,0);
    glutMainLoop();
}
