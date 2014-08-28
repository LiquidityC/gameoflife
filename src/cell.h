#ifndef _CELL_H
#define _CELL_H

#include "renderable.h"

class SDL_Surface;

class Cell : public Renderable
{
	private:
		const unsigned int size = 2;
		bool visible = false;
		bool visible_next_iteration = false;
		bool unchanged = false;
		unsigned int xpos, ypos;

	public:

		Cell(unsigned int x, unsigned int y) : xpos(x), ypos(y) { };

		bool isVisible() const { return visible; };

		void setVisible(bool b) { visible_next_iteration = b; };

		void update();

		virtual void render(SDL_Surface*) const;
};

#endif
