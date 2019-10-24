/*
 * screen.h
 *
 *  Created on: 23 Jul 2019
 *      Author: joshmurr
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>

#define PI 3.14159265359

class Screen {
private:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;

    int COLS, ROWS;

    int RESOLUTION;
    int mouseX, mouseY;
    int mouseClickX, mouseClickY;

    double getRoseX(int, float, float, float);
    double getRoseY(int, float, float, float);

public:
	Screen();
    Screen(int width, int height, int res);
    bool QUIT;
    bool ANIMATING;
    int ANIMATION_RATE;
	bool init();
	void update();
    void setAnimating(bool);
	void handleEvents();
    void displayGrid();
	void close();
    void writeInfo();
    void circle(float, float, float, int);
    void rose(float, float, float, float, float, float);

    int getWidth();
    int getHeight();

    float getMouseX();
    float getMouseY();
};

#endif /* SCREEN_H_ */
