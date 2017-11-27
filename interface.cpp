//
// Created by enio on 17/11/17.
//

#include "interface.h"

Interface::Interface(int r, int g, int b) {
	red = r;
	green = g;
	blue = b;
}

void Interface::debugPoints() {
	for (int i = -20; i <= 20; i++) {
		for (int j = -20; j <= 20; j++) {
			displayTextLarge(i,j,("."));
		}
	}
}
void Interface::displayTextSmall(float x, float y, const char *text) {
    int j = strlen(text);
    glColor3f(red, green, blue);
    glRasterPos2f(x, y);
    for(int i = 0; i < j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]);
    }
}
void Interface::displayTextMedium(float x, float y, const char *text) {
    int j = strlen(text);
    glColor3f(red, green, blue);
    glRasterPos2f(x, y);
    for(int i = 0; i < j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}
void Interface::displayTextLarge(float x, float y, const char *text) {
    int j = strlen(text);
    glColor3f(red, green, blue);
    glRasterPos2f(x, y);
    for(int i = 0; i < j; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}
void Interface::drawInterface(int fps, double animation_speed, Ship* nave) {
	//Top Interface
	//Left - Running Data
	displayTextSmall(-3.5,2.5,(to_string(fps)+" FPS").c_str());
	//Right - Simulation Data
	if(animation_speed == 0.01)
		displayTextSmall(2.75,2.5,("Speed: x0.01"));
	if(animation_speed == 0.1)
		displayTextSmall(2.75,2.5,("Speed: x0.1"));
	if(animation_speed == 0.5)
		displayTextSmall(2.75,2.5,("Speed: x0.5"));
	if(animation_speed == 1.0)
		displayTextSmall(2.75,2.5,("Speed: x1"));
	if(animation_speed == 2.0)
		displayTextSmall(2.75,2.5,("Speed: x2"));
	if(animation_speed == 5.0)
		displayTextSmall(2.75,2.5,("Speed: x5"));
	if(animation_speed == 10.0)
		displayTextSmall(2.75,2.5,("Speed: x10"));
	if(animation_speed == 20.0)
		displayTextSmall(2.75,2.5,("Speed: x20"));
	if(animation_speed == 50.0)
		displayTextSmall(2.75,2.5,("Speed: x50"));
	if(animation_speed == 100.0)
		displayTextSmall(2.75,2.5,("Speed: x100"));
	if(animation_speed == 1000.0)
		displayTextSmall(2.75,2.5,("Speed: x1000"));
	//Bottom Interface
	//Left - Angle Data
	displayTextLarge(-3.125,-2,("Ship Orientation"));
	displayTextMedium(-3.0,-2.25,("Vertical: "+to_string(((-1)*(int)nave->getAng()[0])+360)+" degrees").c_str());
	displayTextMedium(-3.0,-2.5,("Horizontal: "+to_string((int)nave->getAng()[1])+" degrees").c_str());
	//Middle - Position Data
	displayTextLarge(-0.5,-2,("Ship Position"));
	displayTextMedium(-1.25,-2.375,("X-Axis: "+to_string((int)nave->getPos()[0])).c_str());
	displayTextMedium(-0.25,-2.375,("Y-Axis: "+to_string((int)nave->getPos()[1])).c_str());
	displayTextMedium(0.75,-2.375,("Z-Axis: "+to_string((int)nave->getPos()[2]-500)).c_str());
	//Right - Body Data
	displayTextLarge(2.0,-2,("Speed"));
	displayTextMedium(1.885,-2.25,(to_string(nave->getSpeed()[0])+" s.u.").c_str());
	if(nave->getSpeed()[0] >= nave->getSpeed()[1])
		displayTextMedium(1.75,-2.5,("Max speed reached!"));
	if(nave->getSpeed()[0] <= 0)
		displayTextMedium(1.75,-2.5,("Ship is not moving!"));
}
void Interface::drawBox(float w, float h, int r, int g, int b) {
	glColor3f(r, g, b);
	float x1 = -w/2;
	float y1 = -30 + h/2;
	float x2 = w/2;
	float y2 = -30;
	glBegin(GL_POLYGON);
	glVertex3f(x1, y1, -10);
	glVertex3f(x2, y1, -10);
	glVertex3f(x2, y2, -10);
	glVertex3f(x1, y2, -10);
	glEnd();
	glRectf(x1, y1, x2, y2);
	//glRectf(-10, 10, 10, -10);
	//glColor3f(1.0f, 0.0f, 0.0f);
    //glRectf(-0.75f,0.75f, 0.75f, -0.75f);
}
