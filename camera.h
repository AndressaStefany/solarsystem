//
// Created by vitor on 16/11/17.
//

#ifndef SOLARSYSTEM_CAMERA_H
#define SOLARSYSTEM_CAMERA_H

#pragma once

#include <GL/glut.h>
#include <map>
#include "loading.h"

extern char keys[255];
extern map<int,bool> spkeys;

class Camera
{
    vec3 pos, dir;
    double dx= 0, dy= 0, last_x= 0, last_y= 0, zoom= 0;
    int btt[3]= {0,0,0};
    const double speed= 100;
public:
    explicit Camera(vec3 ini_pos);
    void mouse(int button, int state, int x, int y);
    void motion(int x, int y);
    void update(double delta_time);
    void follow(vec3 f, vec2 ang);
    void posiciona();
};


#endif //SOLARSYSTEM_CAMERA_H
