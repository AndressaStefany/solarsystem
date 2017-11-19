//
// Created by vitor on 16/11/17.
//

#include "planet.h"

Planet::Planet(string arquivo, vec3 pos_, double a_, double b_,
               double vtranslation_, double vrotation_,
               double angh_, double angv_, double inclination_) : Loading(arquivo)
{
    pos= pos_;
    a = a_;
    b = b_;
    vtranslation = (vtranslation_!=0)?((2*M_PI)/vtranslation_):0;
    vrotation= (vrotation_!=0)?(360.0/vrotation_):0;//vrotation_/vtranslation_*2*M_PI;
    angh= angh_;
    angv= angv_;
    inclination= inclination_;
    genTrajectoryList();
}
void Planet::genTrajectoryList()
{
    trajectoryList = glGenLists(1);
    if(trajectoryList == 0)
        throw "Erro on generating list";
    double x;
    glNewList(trajectoryList, GL_COMPILE);
    glPushMatrix();
    glColor3f(1,1,1);
    glRotated(angv,1,0,0);
    glRotated(angh,0,1,0);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<200; i++)
    {
        x=i/200.0*M_PI*2;
        glVertex3d(a*cos(x), b*sin(x), 0);
    }
    glEnd();
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
    glRotated(inclination, 0,0,1);
    glRotated(t2, 0,1,0);
    Loading::draw();
    glPopMatrix();
}

void Planet::update(double delta_time) {
    t1+=vtranslation*delta_time;
    t2+=vrotation*delta_time;
    t1= fmod(t1, 2*M_PI);
    t2= fmod(t2, 360);
}
