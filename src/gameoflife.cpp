#include <iostream>
#include <SDL2/SDL.h>

#include "cellcontainer.h"
#include "timer.h"

const int SCREEN_WIDTH 				= 640;
const int SCREEN_HEIGHT 			= 480;
const int SCREEN_FPS 				= 20;
const int SCREEN_TICKS_PER_FRAME 	= 1000 / SCREEN_FPS;

int main( int argc, char* args[] )
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
		std::cerr << "Failed to init video: " << SDL_GetError() << std::endl;
		return -1;
	}

	window = SDL_CreateWindow( "Game Of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if (window == NULL) {
		std::cerr << "Window could not be created: " << SDL_GetError() << std::endl;
		return -1;
	}

	screenSurface = SDL_GetWindowSurface( window );

	bool quit = false;
	SDL_Event e;

	CellContainer cellContainer;
	cellContainer.init(SCREEN_WIDTH, SCREEN_HEIGHT);

	Timer fpsCapTimer;

	// Main loop
	while (!quit) {

		fpsCapTimer.start();
		
		while (SDL_PollEvent (&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_MOUSEMOTION) {
				int x, y;

				x = e.motion.x;
				y = e.motion.y;

				cellContainer.mouseMotion(x, y);
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_RETURN:
						cellContainer.randomize();
						break;
					case SDLK_BACKSPACE:
						cellContainer.invert();
						break;
					default:
						break;
				}
			}
		}

		// Move stuff
		cellContainer.repopulate();

		cellContainer.render(screenSurface);

		SDL_UpdateWindowSurface( window );

		// Cap the frame rate
		int frameTicks = fpsCapTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME) {
			SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
		}
	}

	SDL_DestroyWindow( window );

	SDL_Quit();

	return 0;
}
