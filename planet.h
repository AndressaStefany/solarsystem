//
// Created by vitor on 16/11/17.
//

#ifndef SOLARSYSTEM_PLANET_H
#define SOLARSYSTEM_PLANET_H

#pragma once

#include <GL/glut.h>
#include "loading.h"

class Planet : public Loading{
    float a, b, t=0, vang;
    double angh, angv;
    vec3 pos;
public:
    Planet(string arquivo, vec3 pos_, float a_, float b_,
           float vang_,float angh_, float angv_);
    void draw();
};



#endif //SOLARSYSTEM_PLANET_H
