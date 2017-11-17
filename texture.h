//
// Created by vitor on 12/11/17.
//

#ifndef RACEGAME_TEXTURE_H
#define RACEGAME_TEXTURE_H


#pragma once
#include <GL/gl.h>
#include <cstring>
#include <cstdio>
#include <string>

using namespace std;

class Texture
{
    unsigned int textureID;
public:
    explicit Texture(string name);
    ~Texture();
    void loadBMP(string name);
    void setTexture(void* data, int w, int h, GLenum format);
    unsigned int getID() const { return textureID; }
};



#endif //RACEGAME_TEXTURE_H
