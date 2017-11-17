#ifndef SOLARSYSTEM_INTERFACE_H
#define SOLARSYSTEM_INTERFACE_H

#pragma once
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <string.h>

using namespace std;

class Interface {
public:
	char buffer[20]={'\0'};

	Interface();
    void debugPoints();
	void displayText(float x, float y, int r, int g, int b, const char *string );
	void printText(float pos_x, float pos_y, const char *text);
	void printVariable(float pos_x, float pos_y, float f);
	void drawBox(float w, float h, int r, int g, int b);
};

#endif //SOLARSYSTEM_INTERFACE_H
