//
// Created by andressa on 04/11/17.
//

#ifndef SOLARSYSTEM_LOADING_H
#define SOLARSYSTEM_LOADING_H

#pragma once
#include <GL/gl.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>

#include "texture.h"
#include "algebra.h"

using namespace std;

vector<string> split(string name, char limite);

struct material
{
    float Ka[4], Kd[4], Ks[4], Ke[4];
    float Ns= 0;
    Texture* mapK= NULL, *map_Bump= NULL;
    string name;
};
struct face
{
    vec3 v[3];
    vec3 n[3];
    vec2 t[3];
    double area()
    {
        vec3 a=v[1]-v[0], b=v[2]-v[0];
        return sqrt(pow(a[1]*b[2]-a[2]*b[1],2)+pow(a[2]*b[0]-a[0]*b[2],2)+
                    pow(a[0]*b[1]-a[1]*b[0],2));
    }
    vec3 centroid()
    {
        return (v[0]+v[1]+v[2])/3.0;
    }
};
struct mesh
{
    vector<face> faces;
    material* mat;
    string name_mat;
    vec3 centroid()
    {
        vec3 res= vec3(0,0,0);
        double total_area= 0;
        for(auto& f: faces)
        {
            res+= f.centroid()*f.area();
            total_area+=f.area();
        }
        return res/total_area;
    }
};
struct object
{
    vector<mesh> meshs;
    string name;
};

class Loading {
protected:
    GLuint objList;
    vector<object> obj;
    vector<material> mat;
    void load_obj(string arquivo);
    void load_mtl(string arquivo);
    void obj_mtl();
    virtual void generateList();
public:
    Loading(string arquivo);
    virtual void draw();
};


#endif //SOLARSYSTEM_LOADING_H
