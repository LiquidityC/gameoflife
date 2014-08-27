#include <iostream>
#include <SDL2/SDL.h>

#include "cellcontainer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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

	// Main loop
	while (!quit) {
		
		while (SDL_PollEvent (&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_MOUSEMOTION) {
				int x, y;

				x = e.motion.x;
				y = e.motion.y;

				cellContainer.mouseMotion(x, y);
			}
		}

		// Move stuff
		cellContainer.repopulate();

		//Fill the surface black 
		SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x000000, 0x000000, 0x000000 ) ); 
		cellContainer.render(screenSurface);

		SDL_UpdateWindowSurface( window );

		SDL_Delay ( 100 );
	}

	SDL_DestroyWindow( window );

	SDL_Quit();

	return 0;
}
