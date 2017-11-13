//
// Created by vitor on 12/11/17.
//

#ifndef RACEGAME_TEXTURE_H
#define RACEGAME_TEXTURE_H


#include <GL/gl.h>
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

class Texture
{
    unsigned int textureID;
public:
    Texture(string name);
    ~Texture();
    void loadBMP(string name);
    void setTexture(void* data, int w, int h, int format);
    unsigned int getID() const { return textureID; }
};



#endif //RACEGAME_TEXTURE_H
