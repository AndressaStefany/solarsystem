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

class Nave : public Loading
{
public:
    bool open= false;
    Nave(string obj) : Loading(obj)
    {

    }
    void draw()
    {
        glPushMatrix();
        for(auto& o:obj){
            for(auto& m:o.meshs) {
                glPushMatrix();

                if(o.name == "Cube.004_Cube.001")
                {
                    static double ang=0;
                    if(open)
                        ang= ang>50?51:ang+1;
                    else
                        ang= ang<1?0:ang-1;
                    glTranslated(m.centroid().n[0], m.centroid().n[1], m.centroid().n[2]+1.5);
                    glRotatef(ang,1,0,0);
                    glTranslated(-m.centroid().n[0], -m.centroid().n[1], -m.centroid().n[2]-1.5);
                    m.mat->Kd[3]= 0.4;
                }

                if(m.mat->mapK) {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, m.mat->mapK->getID());
                }
                glMaterialfv(GL_FRONT, GL_AMBIENT, m.mat->Ka);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, m.mat->Kd);
                glMaterialfv(GL_FRONT, GL_SPECULAR, m.mat->Ks);
                glMaterialfv(GL_FRONT, GL_SHININESS, &m.mat->Ns);
                glMaterialfv(GL_FRONT, GL_EMISSION, m.mat->Ke);
                for(auto& f:m.faces) {
                    glBegin(GL_TRIANGLES);
                    glNormal3dv(f.n[0].n);
                    glTexCoord2dv(f.t[0].n);
                    glVertex3dv(f.v[0].n);

                    glNormal3dv(f.n[1].n);
                    glTexCoord2dv(f.t[1].n);
                    glVertex3dv(f.v[1].n);

                    glNormal3dv(f.n[2].n);
                    glTexCoord2dv(f.t[2].n);
                    glVertex3dv(f.v[2].n);
                    glEnd();
                }
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, 0);
                glPopMatrix();
                glPopMatrix();
            }
        }
        glPopMatrix();
    }
};

#include <random>
class Sky : public Loading
{
    vector<vec3> particles;
    double r= 0.02;
    mt19937 rng;
public:
    Sky(string obj) : Loading(obj), rng(time(NULL))
    {
        createParticles(-20,20);
    }
    void createParticles(double a, double b)
    {
//        mt19937 rng(time(NULL));
        uniform_real_distribution<double> dist(a, b);
        for(int i=0; i<2000; i++)
        {
            particles.emplace_back(dist(rng), dist(rng), dist(rng));
        }
    }
    void draw(vec3 pos)
    {
        glPushMatrix();
        //glTranslatef(pos.n[0], pos.n[1], pos.n[2]);
        //glRotatef(pos.norma()*0.1,1,1,1);
        Loading::draw();
        glPopMatrix();
        /*
        uniform_real_distribution<double> dist_x(pos.n[0]-20, pos.n[0]+20),
                dist_y(pos.n[1]-20, pos.n[1]+20),dist_z(pos.n[2]-20, pos.n[2]+20);
        for(auto& p : particles)
        {
            if((p-pos).norma()>20)
            {
                p= vec3(dist_x(rng), dist_y(rng), dist_z(rng));
                while((p-pos).norma()<5)
                    p= vec3(dist_x(rng), dist_y(rng), dist_z(rng));
            }
        }

        for(auto& p : particles)
        {
            glPushMatrix();
            float k[]= {1,1,1,1};
            uniform_real_distribution<double> bri(-1,1);
            float e= bri(rng);
            float ke[]= {e, e, e, e};
            glMaterialfv(GL_FRONT, GL_AMBIENT, k);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, k);
            glMaterialfv(GL_FRONT, GL_SPECULAR, k);
            glMaterialfv(GL_FRONT, GL_EMISSION, ke);
            glTranslatef(p.n[0], p.n[1], p.n[2]);
            glutSolidSphere(r,5,5);
            glPopMatrix();
        }
         */
    }
};

class Planet : public Loading{
    float a, b, t=0, vang;
    double angh, angv;
    vec3 pos; //, axis, per;
    //double r= 2;
public:
    Planet(string arquivo, vec3 pos_, float a_, float b_, float vang_,
           float angh_, float angv_) : Loading(arquivo)
    {
        t=0;
        a = a_;
        b = b_;
        vang = vang_;
        angh= angh_;
        angv= angv_;
        pos= pos_;
//        axis= vec3(cos(angv)*sin(angh),sin(angv),cos(angv)*cos(angh));
//        per= (axis^vec3(1,0,0))^axis;
//        per=per/per.norma()*r;
    }
    void draw()
    {
        //per= per/per.norma()*r*sqrt(pow(a*cos(t*M_PI/180),2)+pow(b*sin(t*M_PI/180),2));
        //cout << per.norma() << " " << t << endl;
        //vec3 x1= per/per.norma(), x2= axis/axis.norma(), x3= x1^x2;
        glPushMatrix();
        glTranslatef(pos.n[0],pos.n[1],pos.n[2]);
        for(float x=0; x<t; x+=0.01)
        {
//            vec3 per_= per;
            glPushMatrix();
//            glRotatef(x,axis.n[0],axis.n[1],axis.n[2]);
//            glTranslatef(per_.n[0],per_.n[1],per_.n[2]);
//            glRotatef(-x, axis.n[0], axis.n[1], axis.n[2]);
            glRotatef(angv,1,0,0);
            glRotatef(angh,0,1,0);
            glTranslatef(a*cos(x), b*sin(x), 0);
            glutSolidSphere(0.1,2,2);
            glPopMatrix();
        }

        glPushMatrix();
        glutSolidSphere(0.3,10,10);
        glPopMatrix();

//        glRotatef(t,axis.n[0],axis.n[1],axis.n[2]);
//        glTranslatef(per.n[0],per.n[1],per.n[2]);
//        glRotatef(-t,axis.n[0],axis.n[1],axis.n[2]);
        glRotatef(angv,1,0,0);
        glRotatef(angh,0,1,0);
        glTranslatef(a*cos(t), b*sin(t), 0);
        glRotatef(-angh,0,1,0);
        glRotatef(-angv,1,0,0);
        Loading::draw();

        glPopMatrix();

        t+=vang;
    }
};

Sky *ceu;
Nave *teste;
Planet *saturn;

float dx = 0, dy = 0, last_x, last_y, zoom= 15;
int btt[3];
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
    gluPerspective(30,ar,0.1,1000);

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
    glTranslatef(0,0,-zoom);
    glRotatef(dy, 1,0,0);
    glRotatef(dx, 0,1,0);
    glTranslatef(-pos_x,-pos_y,-pos_z);	//Fazer a camera acompanhar a nave

    //Nave
    glPushMatrix();
    glTranslatef(pos_x,pos_y,pos_z);
    glRotatef(ang_v,1,0,0);
    glRotatef(ang_h,0,1,0);

    glutSolidCube(1);
    //teste->draw();	//Frente da nave

    glPopMatrix();
    
    //Referência
    /*glPushMatrix();
    glTranslatef(0,0,10);
    glColor3f(1,1,0);
    glutWireSphere(0.5, 20, 16);
    glPopMatrix(); */

    glPushMatrix();
    //ceu->draw(vec3(pos_x,pos_y,pos_z));
    glPopMatrix();

    //planeta saturno
    glPushMatrix();
    saturn->draw();
    glPopMatrix();

    glutSwapBuffers();
}

void mouse(int botao, int estado, int x, int y)
{
    last_x=x;
    last_y=y;
    switch(botao)
    {
        case GLUT_LEFT_BUTTON: btt[0] = ((GLUT_DOWN==estado)?1:0); break;
        case GLUT_MIDDLE_BUTTON: btt[1] = ((GLUT_DOWN==estado)?1:0); break;
        case GLUT_RIGHT_BUTTON: btt[2] = ((GLUT_DOWN==estado)?1:0); break;
        case 3: zoom -= 0.3; break;
        case 4: zoom += 0.3; break;
        default:
            break;
    }
}

void motion(int x, int y)
{
    if(btt[0])
    {
        dx += (x-last_x)*0.3;
        dy += (y-last_y)*0.3;
    }
    last_x = x;
    last_y = y;
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
       case 'o':
           teste->open= true;
           break;
       case 'p':
           teste->open= false;
           break;
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
    glutTimerFunc(60, time, t);
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

    teste= new Nave("nave");
    ceu= new Sky("sky");
    saturn = new Planet("saturn", vec3(0,1,0), 2, 1, 0.1, 30, 30);

    //glClearColor(0,0,0,0);
    glutMainLoop();
}
