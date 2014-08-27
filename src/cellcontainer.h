#ifndef _CELL_CONTAINER_H
#define _CELL_CONTAINER_H

#include <vector>
#include "renderable.h"
#include "cell.h"

class CellContainer : public Renderable
{
	private:

		std::vector< std::vector<Cell> > cell_matrix;

		unsigned int countNeighborsFor(unsigned int, unsigned int);

	public:

		void init(unsigned int, unsigned int);

		void repopulate();

		void randomize();

		void invert();

		void mouseMotion(int x, int y);

		virtual void render(SDL_Surface*) const;
};

#endif
