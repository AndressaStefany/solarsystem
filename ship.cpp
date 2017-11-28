//
// Created by vitor on 16/11/17.
//

#include "ship.h"

Ship::Ship(string obj, vec3 pos_, vec3 speed_) : Loading(obj)
{
    pos= pos_;
    speed= speed_;
    generateList();
}
vec3 Ship::getPos()
{
    return pos;
}
vec2 Ship::getAng()
{
    return vec2(ang_v, ang_h);
}
vec2 Ship:: getSpeed()
{
	return vec2(sp, max_speed);
}

void Ship::draw()
{
    glPushMatrix();
    glTranslated(pos.n[0],pos.n[1],pos.n[2]);
    glRotatef(ang_h,0,1,0);
    glRotatef(ang_v,1,0,0);
    glRotatef(180,0,1,0);

    glScalef(0.3,0.3,0.3);
    glCallList(objList);

    glTranslated(cabinCentroid.n[0], cabinCentroid.n[1], cabinCentroid.n[2]+1.5);
    glRotated(ang_cabin,1,0,0);
    glTranslated(-cabinCentroid.n[0], -cabinCentroid.n[1], -cabinCentroid.n[2]-1.5);

    //glScalef(0.3,0.3,0.3);
    glCallList(listCabin);
    glPopMatrix();
}

void Ship::update(double delta_time)
{
    if(keys['o'])
        open= true;
    if(keys['p'])
        open= false;

    if(open)
        ang_cabin= ang_cabin>49?55:ang_cabin+200*delta_time;
    else
        ang_cabin= ang_cabin<6?0:ang_cabin-200*delta_time;

    vec3 dir= vec3(cos(-ang_v*M_PI/180.0)*sin(ang_h*M_PI/180.0),
                   sin(-ang_v*M_PI/180.0),
                   cos(-ang_v*M_PI/180.0)*cos(ang_h*M_PI/180.0));

    if(keys['z'] || keys['Z'])
    {
        sp+=acceleration;
		if(sp > max_speed)
			sp = max_speed;
//        speed.n[0] += acceleration*sin(ang_h);
//        speed.n[1] += -acceleration*sin(ang_v);
//        speed.n[2] += (acceleration*cos(ang_v) + acceleration*cos(ang_h));
//        if (speed.n[0] > max_speed) {
//            speed.n[0] = max_speed;
//        }
//        if (speed.n[1] > max_speed) {
//            speed.n[1] = max_speed;
//        }
//        if (speed.n[2] > max_speed) {
//            speed.n[2] = max_speed;
//        }
    }
    if(keys['x'] || keys['X'])
    {
        sp-=acceleration;
		if(sp < 0)
			sp = 0;
//        if (speed.n[0] >= 0) {
//            speed.n[0] -= acceleration*sin(ang_h);
//        } else {
//            speed.n[0] += acceleration*sin(ang_h);
//        }
//        if (speed.n[1] >= 0) {
//            speed.n[1] -= -acceleration*sin(ang_v);
//        } else {
//            speed.n[1] += -acceleration*sin(ang_v);
//        }
//        if (speed.n[2] >= 0) {
//            speed.n[2] -= (acceleration*cos(ang_v) + acceleration*cos(ang_h));
//        } else {
//            speed.n[2] += (acceleration*cos(ang_v) + acceleration*cos(ang_h));
//        }
//        if (speed.n[0] < -max_speed) {
//            speed.n[0] = -max_speed;
//        }
//        if (speed.n[1] < -max_speed) {
//            speed.n[1] = -max_speed;
//        }
//        if (speed.n[2] < -max_speed) {
//            speed.n[2] = -max_speed;
//        }
    }

    if(spkeys[GLUT_KEY_UP])
    {
        ang_v -= turn_speed*delta_time;
    }
    if(spkeys[GLUT_KEY_DOWN])
    {
        ang_v += turn_speed*delta_time;
    }
    if(spkeys[GLUT_KEY_LEFT])
    {
        ang_h += turn_speed*delta_time;
    }
    if(spkeys[GLUT_KEY_RIGHT])
    {
        ang_h -= turn_speed*delta_time;
    }
    ang_v=fmod(ang_v,360);
    ang_h=fmod(ang_h,360);
    pos+=dir*sp*delta_time;
}

void Ship::generateList() {
    listCabin = glGenLists(1);
    if(listCabin == 0)
        throw "Erro on generateList";
    glNewList(listCabin, GL_COMPILE);
    for(auto& o:obj){
        for(auto& m:o.meshs) {
            if(o.name == "Cube.004_Cube.001")
            {
                cabinCentroid= m.centroid();
                glPushMatrix();
                m.mat->Kd[3]= 0.4;
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
    }
    glEndList();

    objList = glGenLists(1);
    if(objList  == 0)
        throw "Erro on generateList";
    glNewList(objList, GL_COMPILE);
    for(auto& o:obj){
        for(auto& m:o.meshs) {
            if(o.name != "Cube.004_Cube.001")
            {
                glPushMatrix();
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
    }
    glEndList();
}
