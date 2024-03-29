/*
 * screen.cpp
 *
 *  Created on: 23 Jul 2019
 *      Author: joshmurr
 */

#include "screen.h"

Screen::Screen(){
    m_window = NULL;
    m_renderer = NULL;
    SCREEN_WIDTH = 600;
    SCREEN_HEIGHT = 400;
    RESOLUTION = 20;
    ANIMATING = false;
    ANIMATION_RATE = 250; // 50 mSeconds
    QUIT = false;
}

Screen::Screen(int width, int height, int res){
    m_window = NULL;
    m_renderer = NULL;
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    RESOLUTION = res;
    ANIMATING = false;
    ANIMATION_RATE = 50; // 50 mSeconds
    QUIT = false;
}

bool Screen::init() {
    // Init library, exit and log if failed
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init - SDL_Init: %s\n", SDL_GetError());
		return false;
	}

    // Try to create window, log and exit if failed
    if(SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &m_window, &m_renderer) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init - SDL_CreateWindowAndRenderer: %s\n", SDL_GetError());
        return false;
    }

    COLS = SCREEN_WIDTH/RESOLUTION;
    ROWS = SCREEN_HEIGHT/RESOLUTION;
    return true;
}


void Screen::handleEvents(){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            QUIT = true;
        } else if (event.type == SDL_MOUSEMOTION){
            // Mouse DRAG
            if(event.motion.state & (SDL_BUTTON_LMASK | SDL_BUTTON_RMASK)){
                mouseX = event.motion.x;
                mouseY = event.motion.y;
            }
        } else if (event.type == SDL_MOUSEBUTTONDOWN){
            // Mouse CLICK
            mouseClickX = event.motion.x;
            mouseClickY = event.motion.y;
            
        } else if (event.type == SDL_KEYDOWN){
            if (event.key.keysym.sym == SDLK_SPACE){
                // SPACEBAR
                ANIMATING = false;
            } else if (event.key.keysym.sym == SDLK_c) {
                // c Button
            } else if (event.key.keysym.sym == SDLK_q){
                ANIMATING = false;
                QUIT = true;
            }
        }
    }
}

void Screen::setAnimating(bool animating){
    ANIMATING = animating;
}


void Screen::displayGrid(){
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    // Draw row lines
    for(int i=0; i<ROWS; i++){
        SDL_RenderDrawLine(m_renderer, 0, RESOLUTION*i, SCREEN_WIDTH, RESOLUTION*i);
    }
    // Draw col lines
    for(int i=0; i<COLS; i++){
        SDL_RenderDrawLine(m_renderer, RESOLUTION*i, 0, RESOLUTION*i, SCREEN_HEIGHT);
    }
    SDL_RenderPresent(m_renderer);
}

void Screen::circle(float x, float y, float r, int segs){
    float spacing = (PI*2)/segs;

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    float currentX = x+(cos(0) * r);
    float currentY = y+(sin(0) * r);
    for(int i=0; i<segs; i++){
        float nextX = x+(cos(spacing * i) * r);
        float nextY = y+(sin(spacing * i) * r);
        SDL_RenderDrawLine(m_renderer, currentX, currentY, nextX, nextY);
        currentX = nextX;
        currentY = nextY;
    }
    SDL_RenderDrawLine(m_renderer, currentX, currentY, x+(cos(0) * r), y+(sin(0) * r));
    SDL_RenderPresent(m_renderer);
}

double Screen::getRoseX(int i, float s, float p1, float p2){
    return sin(i*s*p1)*cos(i*s*p2);
}
double Screen::getRoseY(int i, float s, float p1, float p2){
    return sin(i*s*p1)*sin(i*s*p2);
}

void Screen::rose(float x, float y, float r, float segs, float p1, float p2){
    float spacing = (PI*2)/segs;

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    float currentX = x + getRoseX(0, spacing, p1, p2)*r;
    float currentY = y + getRoseY(0, spacing, p1, p2)*r;

    for(int i=0; i<segs; i++){
        float nextX = x + getRoseX(i, spacing, p1, p2)*r;
        float nextY = y + getRoseY(i, spacing, p1, p2)*r;
        SDL_RenderDrawLine(m_renderer, currentX, currentY, nextX, nextY);
        currentX = nextX;
        currentY = nextY;
    }
    SDL_RenderDrawLine(m_renderer, currentX, currentY, x + getRoseX(0, spacing, p1, p2)*r, y+getRoseY(0, spacing, p1, p2)*r);
    SDL_RenderPresent(m_renderer);
}

float Screen::getMouseX(){
    return mouseX;
}

float Screen::getMouseY(){
    return mouseY;
}

void Screen::writeInfo(){
    std::cout << "SCREEN_WIDTH: " << SCREEN_WIDTH << '\n';
    std::cout << "SCREEN_HEIGHT: " << SCREEN_HEIGHT << '\n';
    std::cout << "COLS: " << COLS << " ROWS: " << ROWS << '\n';
    std::cout <<"RESOLUTION: " << RESOLUTION << std::endl;
}


/*void Screen::clear() {
 *    memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
 *}
 */

void Screen::update() {
	SDL_RenderPresent(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 200, 255);
	SDL_RenderClear(m_renderer);
}

/*
 *void Screen::drawRect(int x, int y, int w, int h, int color){
 *    SDL_Rect rect;
 *
 *    rect.x = x;
 *    rect.y = y;
 *    rect.w = w;
 *    rect.h = h;
 *
 *    int bwcolor = 255*color;
 *
 *    SDL_SetRenderDrawColor(m_renderer, bwcolor, bwcolor, bwcolor, 255);
 *    SDL_RenderFillRect(m_renderer, &rect);
 *
 *}
 */

void Screen::close() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

int Screen::getWidth(){
    return SCREEN_WIDTH;
}

int Screen::getHeight(){
    return SCREEN_HEIGHT;
}
