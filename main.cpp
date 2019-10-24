#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>
#include "screen.h"

double sinWave(Uint32 tick);
double cosWave(Uint32 tick);

int main() {
    Uint32 ticks;
	Screen screen(600, 400, 10);

	if (!screen.init()) {
        std::cout << "Error initializing SDL..." << std::endl;
	}
    screen.setAnimating(true);
    ticks = SDL_GetTicks();
    //screen.writeInfo();
	while (!screen.QUIT) {

        screen.handleEvents();
		//screen.display_grid();
        //screen.circle(300, 200, generateSineWave(ticks)*150, 30);
        //screen.rose(300.0, 200.0, 150.0, 200.0, 3.0, 4.0);
        screen.rose(screen.getMouseX(), screen.getMouseY(), 150.0, 200.0, 3.0, 4.0);

        if(screen.ANIMATING && (SDL_GetTicks() - ticks) > screen.ANIMATION_RATE){
            //screen.step();
            ticks = SDL_GetTicks();
        }
	}

	screen.close();
	return 0;
}

double sinWave(Uint32 tick){
    return sin(tick);    
}
double cosWave(Uint32 tick){
    return cos(tick);    
}
