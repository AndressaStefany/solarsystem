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
    float ang_v = 0, ang_h = 0, ang_cabin = 0, sp = 0;
    const float max_speed = 10, acceleration = 0.25, turn_speed = 45;
    GLuint listCabin;
    vec3 cabinCentroid;
    void generateList();
public:
    Ship(string obj, vec3 pos_, vec3 speed_);
    vec3 getPos();
    vec2 getAng();
	vec2 getSpeed();
    void draw();
    void update(double delta_time);
    friend class Camera;
};


#endif //SOLARSYSTEM_SHIP_H
