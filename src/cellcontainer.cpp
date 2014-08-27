#include <vector>
#include <iostream>
#include <cstdlib>

#include "cellcontainer.h"
#include "cell.h"

using namespace std;

void CellContainer::init(unsigned int width, unsigned int height)
{
	unsigned int mWidth = (width - (width % 2)) / 2;
	unsigned int mHeight = (height - (height % 2)) / 2;

	for (size_t i = 0; i < mHeight; i++) {
		std::vector<Cell> row;
		for (size_t j = 0; j < mWidth; j++) {
			Cell cell(j*2, i*2);
			row.push_back(cell);
		}
		cell_matrix.push_back(row);
	}

	randomize();
}

void CellContainer::randomize()
{
	for (size_t i = 0; i < cell_matrix.size(); i++) {
		for (size_t j = 0; j < cell_matrix[i].size(); j++) {
			cell_matrix[i][j].setVisible(rand() % 2 == 1);
			cell_matrix[i][j].update();
		}
	}
}

void CellContainer::invert()
{
	Cell* c;
	for (size_t i = 0; i < cell_matrix.size(); i++) {
		for (size_t j = 0; j < cell_matrix[i].size(); j++) {
			c = &(cell_matrix[i][j]);
			c->setVisible(!c->isVisible());
			c->update();
		}
	}
}

void CellContainer::repopulate()
{
	for (size_t i = 0; i < cell_matrix.size(); i++) {
		for (size_t j = 0; j < cell_matrix[i].size(); j++) {
			unsigned int neighborCount = countNeighborsFor(j, i);
			Cell* c = &(cell_matrix[i][j]);
			if (c->isVisible()) {
				if (neighborCount < 2) {
					c->setVisible(false);
				} else if (neighborCount > 3) {
					c->setVisible(false);
				}
			} else {
				if (neighborCount == 3) {
					c->setVisible(true);
				}
			}
		}
	}

	for (size_t i = 0; i < cell_matrix.size(); i++) {
		for (size_t j = 0; j < cell_matrix[i].size(); j++) {
			cell_matrix[i][j].update();
		}
	}
}

unsigned int CellContainer::countNeighborsFor(unsigned int x, unsigned int y)
{
	unsigned int count = 0;

	int dx, dy;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {

			if (i == 0 || j == 0) {
				continue;
			}
			dx = x + i;
			dy = y + j;

			if (dx < 0 || dy < 0) {
				continue;
			}

			if (dy >= static_cast<int>(cell_matrix.size()) || dx >= static_cast<int>(cell_matrix[dy].size())) {
				continue;
			}

			count += cell_matrix[dy][dx].isVisible() ? 1 : 0;
		}
	}

	return count;
}

void CellContainer::render(SDL_Surface* surface) const
{
	for (size_t i = 0; i < cell_matrix.size(); i++) {
		for (size_t j = 0; j < cell_matrix[i].size(); j++) {
			cell_matrix[i][j].render(surface);
		}
	}
}

void CellContainer::mouseMotion(int x, int y)
{
	int xpos = (x - (x % 2)) / 2;
	int ypos = (y - (y % 2)) / 2;

	if (ypos+5 >= static_cast<int>(cell_matrix.size())) {
		return;
	}
	if (xpos+5 >= static_cast<int>(cell_matrix[ypos].size())) {
		return;
	}

	for (unsigned int i = 0; i < 6; i++) {
		cell_matrix[ypos+i][xpos].setVisible(true);
		cell_matrix[ypos][xpos+i].setVisible(true);
	}
}
