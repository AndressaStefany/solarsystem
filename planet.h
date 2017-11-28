//
// Created by vitor on 16/11/17.
//

#ifndef SOLARSYSTEM_PLANET_H
#define SOLARSYSTEM_PLANET_H

#pragma once

#include <GL/glut.h>
#include "loading.h"

class Planet : public Loading{
    double a, b, t1=0, t2=0, vtranslation, vrotation;
    double angh, angv, inclination;
    vec3 pos;
    GLuint trajectoryList;
    void genTrajectoryList();
public:
    static bool withTrajectory;
    Planet(string arquivo, vec3 pos_, double a_, double b_, double vtranslation_, double vrotation_,
           double angh_, double angv_, double inclination_);
    void draw();
    void update(double delta_time);
    friend class Camera;
    friend class Satellite;
};


#endif //SOLARSYSTEM_PLANET_H
