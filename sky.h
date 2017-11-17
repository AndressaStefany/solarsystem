//
// Created by vitor on 16/11/17.
//

#ifndef SOLARSYSTEM_SKY_H
#define SOLARSYSTEM_SKY_H

#pragma once

#include "loading.h"
#include <GL/glut.h>
#include <random>

class Sky : public Loading
{
    vector<vec3> particles;
    double r= 0.02;
    bool particles_enable= false;
    random_device rnd;
public:
    explicit Sky(string obj);
    void createParticles(double a, double b);
    void draw(vec3 pos);
};

#endif //SOLARSYSTEM_SKY_H
