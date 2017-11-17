//
// Created by vitor on 16/11/17.
//

#include "planet.h"

Planet::Planet(string arquivo, vec3 pos_, float a_, float b_, float vang_,
float angh_, float angv_) : Loading(arquivo)
{
    t=0;
    a = a_;
    b = b_;
    vang = vang_;
    angh= angh_;
    angv= angv_;
    pos= pos_;
}
void Planet::draw()
{
    glPushMatrix();
    glTranslated(pos.n[0],pos.n[1],pos.n[2]);
    double x;
    for(int i=0; i<200; i++)
    {
        x=i/200.0*M_PI*2;
        glPushMatrix();
        glRotated(angv,1,0,0);
        glRotated(angh,0,1,0);
        glTranslated(a*cos(x), b*sin(x), 0);
        glutSolidSphere(0.1,2,2);
        glPopMatrix();
    }

    glRotated(angv,1,0,0);
    glRotated(angh,0,1,0);
    glTranslated(a*cos(t), b*sin(t), 0);
    glRotated(-angh,0,1,0);
    glRotated(-angv,1,0,0);
    Loading::draw();

    glPopMatrix();

    t+=vang;
}