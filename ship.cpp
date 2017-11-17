//
// Created by vitor on 16/11/17.
//

#include "ship.h"

Ship::Ship(string obj, vec3 pos_, vec3 speed_) : Loading(obj)
{
    pos= pos_;
    speed= speed_;
}
vec3 Ship::getPos()
{
    return pos;
}
void Ship::draw()
{
    glPushMatrix();
    glTranslated(pos.n[0],pos.n[1],pos.n[2]);
    glRotatef(ang_h,0,1,0);
    glRotatef(ang_v,1,0,0);
    glRotatef(180,0,1,0);
    for(auto& o:obj){
        for(auto& m:o.meshs) {
            glPushMatrix();

            if(o.name == "Cube.004_Cube.001")
            {
                static double ang=0;
                if(open)
                    ang= ang>50?51:ang+5;
                else
                    ang= ang<1?0:ang-5;
                glTranslated(m.centroid().n[0], m.centroid().n[1], m.centroid().n[2]+1.5);
                glRotated(ang,1,0,0);
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
        }
    }
    glPopMatrix();
}
void Ship::update()
{
    if(keys['o'])
        open= true;
    if(keys['p'])
        open= false;

    if(keys['z'] || keys['Z'])
    {
        speed.n[0] += acceleration*sin(ang_h);
        speed.n[1] += -acceleration*sin(ang_v);
        speed.n[2] += (acceleration*cos(ang_v) + acceleration*cos(ang_h));
        if (speed.n[0] > max_speed) {
            speed.n[0] = max_speed;
        }
        if (speed.n[1] > max_speed) {
            speed.n[1] = max_speed;
        }
        if (speed.n[2] > max_speed) {
            speed.n[2] = max_speed;
        }
    }
    if(keys['x'] || keys['X'])
    {
        if (speed.n[0] >= 0) {
            speed.n[0] -= acceleration*sin(ang_h);
        } else {
            speed.n[0] += acceleration*sin(ang_h);
        }
        if (speed.n[1] >= 0) {
            speed.n[1] -= -acceleration*sin(ang_v);
        } else {
            speed.n[1] += -acceleration*sin(ang_v);
        }
        if (speed.n[2] >= 0) {
            speed.n[2] -= (acceleration*cos(ang_v) + acceleration*cos(ang_h));
        } else {
            speed.n[2] += (acceleration*cos(ang_v) + acceleration*cos(ang_h));
        }
        if (speed.n[0] < -max_speed) {
            speed.n[0] = -max_speed;
        }
        if (speed.n[1] < -max_speed) {
            speed.n[1] = -max_speed;
        }
        if (speed.n[2] < -max_speed) {
            speed.n[2] = -max_speed;
        }
    }

    if(spkeys[GLUT_KEY_UP])
    {
        ang_v += 1;
        if (ang_v > 90) {
            ang_v = 90;
        }
    }
    if(spkeys[GLUT_KEY_DOWN])
    {
        ang_v -= 1;
        if (ang_v < -90) {
            ang_v = -90;
        }
    }
    if(spkeys[GLUT_KEY_LEFT])
    {
        ang_h -= 1;
        if (ang_h < -90) {
            ang_h = -90;
        }
    }
    if(spkeys[GLUT_KEY_RIGHT])
    {
        ang_h += 1;
        if (ang_h > 90) {
            ang_h = 90;
        }
    }

    pos+=speed;
}