//
// Created by vitor on 16/11/17.
//

#ifndef SOLARSYSTEM_SHIP_H
#define SOLARSYSTEM_SHIP_H

#pragma once
#include "loading.h"
#include <GL/glut.h>
#include <map>

extern char keys[255];
extern map<int,bool> spkeys;

class Ship : public Loading
{
    vec3 pos, speed;
    bool open= false;
    float ang_v = 0, ang_h = 0, ang_cabin= 0, sp= 0;
    const float max_speed = 10, acceleration = 0.1, turn_speed= 45;
    GLuint listCabin;
    vec3 cabinCentroid;
    void generateList();
public:
    Ship(string obj, vec3 pos_, vec3 speed_);
    vec3 getPos();
    vec2 getAng();
    void draw();
    void update(double delta_time);
};


#endif //SOLARSYSTEM_SHIP_H
