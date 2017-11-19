//
// Created by vitor on 16/11/17.
//

#ifndef SOLARSYSTEM_CAMERA_H
#define SOLARSYSTEM_CAMERA_H

#pragma once

#include <GL/glut.h>
#include <map>
#include "loading.h"
#include "ship.h"
#include "planet.h"

extern char keys[255];
extern map<int,bool> spkeys;

class Camera
{
    vec3 pos, dir;
    double dx, dy, last_x= 0, last_y= 0, zoom= 0;
    int btt[3]= {0,0,0};
    const double speed= 100;
    Planet* follow_planet= nullptr;
    Ship* follow_ship= nullptr;
    bool free_cam= true;
public:
    explicit Camera(vec3 ini_pos, double angh, double angv);
    void mouse(int button, int state, int x, int y);
    void motion(int x, int y);
    void update(double delta_time);
    void setFollow(Ship* x, double zoom);
    void setFollow(Planet* x, double zoom);
    void setFree();
    void posiciona();
};


#endif //SOLARSYSTEM_CAMERA_H
