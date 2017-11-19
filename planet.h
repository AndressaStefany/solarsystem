//
// Created by vitor on 16/11/17.
//

#ifndef SOLARSYSTEM_PLANET_H
#define SOLARSYSTEM_PLANET_H

#pragma once

#include <GL/glut.h>
#include "loading.h"

class Planet : public Loading{
    float a, b, t1=0, t2=0, vtranslation, vrotation;
    double angh, angv;
    vec3 pos;
    bool withTrajectory= true;
    GLuint trajectoryList;
    void genTrajectoryList();
public:
    Planet(string arquivo, vec3 pos_, float a_, float b_, float vtranslation_, float vrotation_,
           float angh_, float angv_);
    void draw();
    void update(double delta_time);
    friend class Camera;
};



#endif //SOLARSYSTEM_PLANET_H
