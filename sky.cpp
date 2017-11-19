//
// Created by vitor on 16/11/17.
//

#include "sky.h"

Sky::Sky(string obj) : Loading(obj)
{
    createParticles(-20,20);
}
void Sky::createParticles(double a, double b)
{
    uniform_real_distribution<double> dist(a, b);
    for(int i=0; i<2000; i++)
    {
        particles.emplace_back(dist(rnd), dist(rnd), dist(rnd));
    }
}
void Sky::draw(vec3 pos)
{
    glPushMatrix();
    glTranslated(pos.n[0], pos.n[1], pos.n[2]);
    //glRotatef(pos.norma()*0.1,1,1,1);
    Loading::draw();
    glPopMatrix();

    if(particles_enable)
    {
        uniform_real_distribution<double> dist_x(pos.n[0]-20, pos.n[0]+20),
                dist_y(pos.n[1]-20, pos.n[1]+20),dist_z(pos.n[2]-20, pos.n[2]+20);
        for(auto& p : particles)
        {
            if((p-pos).norma()>20)
            {
                p= vec3(dist_x(rnd), dist_y(rnd), dist_z(rnd));
                while((p-pos).norma()<5)
                    p= vec3(dist_x(rnd), dist_y(rnd), dist_z(rnd));
            }
        }

        for(auto& p : particles)
        {
            glPushMatrix();
            float k[]= {1,1,1,1};
            uniform_real_distribution<double> bri(-1,1);
            float e= bri(rnd);
            float ke[]= {e, e, e, e};
            glMaterialfv(GL_FRONT, GL_AMBIENT, k);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, k);
            glMaterialfv(GL_FRONT, GL_SPECULAR, k);
            glMaterialfv(GL_FRONT, GL_EMISSION, ke);
            glTranslated(p.n[0], p.n[1], p.n[2]);
            glutSolidSphere(r,5,5);
            glPopMatrix();
        }
    }
}