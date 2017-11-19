//
// Created by vitor on 16/11/17.
//

#include "planet.h"

Planet::Planet(string arquivo, vec3 pos_, float a_, float b_, float vtranslation_, float vrotation_,
float angh_, float angv_) : Loading(arquivo)
{
    a = a_;
    b = b_;
    vtranslation = vtranslation_;
    vrotation= vrotation_;
    angh= angh_;
    angv= angv_;
    pos= pos_;
    genTrajectoryList();
}
void Planet::genTrajectoryList()
{
    trajectoryList = glGenLists(1);
    if(trajectoryList == 0)
        throw "Erro on generating list";
    glNewList(trajectoryList, GL_COMPILE);
    glPushMatrix();
    glColor3f(1,1,1);
    double x;
    for(int i=0; i<2000; i++)
    {
        x=i/2000.0*M_PI*2;
        glPushMatrix();
        glRotated(angv,1,0,0);
        glRotated(angh,0,1,0);
        glTranslated(a*cos(x), b*sin(x), 0);
        glutSolidSphere(0.5,2,2);
        glPopMatrix();
    }
    glPopMatrix();
    glEndList();
}

void Planet::draw()
{
    glPushMatrix();
    glTranslated(pos.n[0],pos.n[1],pos.n[2]);
    if(withTrajectory)
    {
        glDisable(GL_LIGHTING);
        glCallList(trajectoryList);
        glEnable(GL_LIGHTING);
    }
    glRotated(angv,1,0,0);
    glRotated(angh,0,1,0);
    glTranslated(a*cos(t1), b*sin(t1), 0);
    glRotated(-angh,0,1,0);
    glRotated(-angv,1,0,0);
    glRotatef(t2, 0,1,0);
    Loading::draw();
    glPopMatrix();
}

void Planet::update(double delta_time) {
    t1+=vtranslation*delta_time;
    t2+=vrotation*delta_time;
    t1= fmod(t1, 360);
    t2= fmod(t2, 360);
}
