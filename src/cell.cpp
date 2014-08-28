#include <SDL2/SDL.h>

#include "cell.h"

void Cell::update() 
{ 
	unchanged = false;
	if (visible && visible_next_iteration) {
		unchanged = true;
	}

	visible = visible_next_iteration; 
}

void Cell::render(SDL_Surface* surface) const
{
	Uint32 color = SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF);
	if (unchanged) {
		color = SDL_MapRGB(surface->format, 0xFF, 0x00, 0x00);
	} else if (!visible) {
		color = SDL_MapRGB(surface->format, 0x00, 0x00, 0x00);
	}

	SDL_Rect rect;
	rect.x = xpos;
	rect.y = ypos;
	rect.w = size;
	rect.h = size;

	SDL_FillRect(surface, &rect, color);
}
