//
// Created by enio on 17/11/17.
//

#include "interface.h"

Interface::Interface(){}

void Interface::debugPoints() {
	for (int i = -20; i <= 20; i++) {
		for (int j = -20; j <= 20; j++) {
			printText(i, j, ".");
		}
	}
}
void Interface::displayText(float x, float y, int r, int g, int b, const char *text) {
    int j = strlen(text);
 
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for(int i = 0; i < j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
}
void Interface::printText(float pos_x, float pos_y, const char *text) {
	sprintf(buffer, "%s", text);
	displayText(pos_x, pos_y, 255, 255, 255, buffer);
}
void Interface::printVariable(float pos_x, float pos_y, float f) {
	sprintf(buffer, "%f", f);
	displayText(pos_x, pos_y, 255, 255, 255, buffer);
}
void Interface::drawBox(float w, float h, int r, int g, int b) {
	glColor3f(r, g, b);
	float x1 = -w/2;
	float y1 = -2.5 + h/2;
	float x2 = w/2;
	float y2 = -2.5;
	//glRectf(x1, y1, x2, y2);
	glRectf(-1, 1, 1, -1);
}
