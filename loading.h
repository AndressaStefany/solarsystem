//
// Created by andressa on 04/11/17.
//

#ifndef RACEGAME_LOADING_H
#define RACEGAME_LOADING_H

#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <vector>
#include "algebra.h"

using namespace std;

vector<string> split(string name, char limite);

struct material
{
    float Ka[4], Kd[4], Ks[4], Ke[4];
    float Ns= 0;
//    Texture* mapK= NULL, *map_Bump= NULL;
    string name;
};
struct face
{
    vec3 v[3];
    vec3 n[3];
    vec2 t[3];
};
struct mesh
{
    vector<face> faces;
    material* mat;
    string name_mat;
};
struct object
{
    vector<mesh> meshs;
    string name;
};

class Loading {
public:
    Loading(string arquivo);
    void draw();
private:
    vector<object> obj;
    vector<material> mat;
    void load_obj(string arquivo);
    void load_mtl(string arquivo);
    void obj_mtl();
};


#endif //RACEGAME_LOADING_H
