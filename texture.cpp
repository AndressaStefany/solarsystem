//
// Created by vitor on 12/11/17.
//

#include "texture.h"

Texture::Texture(string name) {
    loadBMP(name);
}

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

void Texture::loadBMP(string name)
{
    FILE *fp;

    fp= fopen(name.c_str(), "r");
    if(!fp)
    {
        throw "File not found "+name;
        //fclose(fp);
    }
    char* heardField= new char[2];
    fread(heardField, 2, sizeof(char), fp);
    if(heardField[0] != 'B' || heardField[1] != 'M')
    {
        fclose(fp);
        throw "Not a bmp file ";
    }
    delete[] heardField;

    unsigned char* data;
    unsigned int width;
    unsigned int height;
    unsigned int dataSize;
    unsigned int bmpDataLocation;
    unsigned short numColorPlanes;
    unsigned short bitsPerPixel;
    unsigned int compressionMethod;

    fseek(fp, 0x000a, SEEK_SET);
    fread(&bmpDataLocation, 1, sizeof(unsigned int), fp);

    fseek(fp, 0x0012, SEEK_SET);
    fread(&width, 1, sizeof(unsigned int), fp);
    fread(&height, 1, sizeof(unsigned int), fp);
    fread(&numColorPlanes, 1, sizeof(unsigned short), fp);
    fread(&bitsPerPixel, 1, sizeof(unsigned short), fp);
    fread(&compressionMethod, 1, sizeof(unsigned int), fp);
    fread(&dataSize, 1, sizeof(unsigned int), fp);

    if(numColorPlanes != 1 || bitsPerPixel != 24 || compressionMethod != 0)
    {
        fclose(fp);
        throw "Not uncompressed bmp 24 bits ";
    }

    data= new unsigned char[dataSize];
    fseek(fp, bmpDataLocation, SEEK_SET);
    fread(data, dataSize, sizeof(unsigned char), fp);
    fclose(fp);

    // inverte as cores  B G R || R G B

    for(unsigned int i=0; i<dataSize; i+=3)
    {
        unsigned char aux= data[i];
        if(i+2 < dataSize)
        {
            data[i]= data[i+2];
            data[i+2]= aux;
        }
    }

//    int len= 4*height*width;
//    unsigned char* data2= new unsigned char[4*height*width];
//    for(int i=0, j=0; i<len; i+=4, j+=3)
//    {
//        data2[i]= data[j+2];
//        data2[i+1]= data[j+1];
//        data2[i+2]= data[j];
//        data2[i+3]= 255;
//    }

    this->setTexture(data, width, height, GL_RGB);

    delete[] data;
}

void Texture::setTexture(void* data, int w, int h, GLenum format)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}
