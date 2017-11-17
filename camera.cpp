//
// Created by vitor on 16/11/17.
//

#include "camera.h"


Camera::Camera(vec3 ini_pos) : pos(ini_pos) {}
void Camera::mouse(int button, int state, int x, int y)
{
    last_x=x;
    last_y=y;
    switch(button)
    {
        case GLUT_LEFT_BUTTON: btt[0] = ((GLUT_DOWN==state)?1:0); break;
        case GLUT_MIDDLE_BUTTON: btt[1] = ((GLUT_DOWN==state)?1:0); break;
        case GLUT_RIGHT_BUTTON: btt[2] = ((GLUT_DOWN==state)?1:0); break;
        case 3: zoom -= 0.3; break;
        case 4: zoom += 0.3; break;
        default:
            break;
    }
}
void Camera::motion(int x, int y)
{
    if(btt[0])
    {
        dx += (x-last_x)*0.3;
        dy += (y-last_y)*0.3;
    }
    last_x = x;
    last_y = y;

    dir.n[0]=cos(dy*M_PI/180.0)*sin(-dx*M_PI/180.0);
    dir.n[1]=sin(dy*M_PI/180.0);
    dir.n[2]=cos(dy*M_PI/180.0)*cos(-dx*M_PI/180.0);
}
void Camera::update()
{
    if(keys['w'])
        pos+=dir*0.4;
    if(keys['s'])
        pos-=dir*0.4;
    if(keys['a'])
        pos-=dir^vec3(0,1,0)*0.4;
    if(keys['d'])
        pos+=dir^vec3(0,1,0)*0.4;
}
void Camera::follow(vec3 f)
{
    if(zoom == 0)
        zoom= 10;
    pos= -f;
}
void Camera::posiciona()
{
    glLoadIdentity();
    glTranslated(0,0,-zoom);
    glRotated(dy, 1,0,0);
    glRotated(dx, 0,1,0);
    glTranslated(pos.n[0],pos.n[1],pos.n[2]);
}