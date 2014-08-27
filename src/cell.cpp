#include <SDL2/SDL.h>

#include "cell.h"

void Cell::render(SDL_Surface* surface) const
{
	if (!visible) {
		return;
	}

	SDL_Rect rect;
	rect.x = xpos;
	rect.y = ypos;
	rect.w = size;
	rect.h = size;

	SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
}
