//
// Created by enio on 17/11/17.
//

#ifndef SOLARSYSTEM_INTERFACE_H
#define SOLARSYSTEM_INTERFACE_H

#pragma once
#include <iostream>
#include <chrono>
#include <GL/gl.h>
#include <GL/glut.h>
#include <string.h>
#include "ship.h"

using namespace std;

class Interface {
public:
	char buffer[20]={'\0'};

	Interface();
    void debugPoints();
	void displayTextSmall(float x, float y, int r, int g, int b, const char *string);
	void displayTextMedium(float x, float y, int r, int g, int b, const char *string);
	void displayTextLarge(float x, float y, int r, int g, int b, const char *string);
	void drawInterface(int fps, double animation_speed, Ship* nave);
	void drawBox(float w, float h, int r, int g, int b);
};

#endif //SOLARSYSTEM_INTERFACE_H
