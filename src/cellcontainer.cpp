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

			if (i == 0 && j == 0) {
				continue;
			}
			dx = x + j;
			dy = y + i;

			if (!coordinatesExist(dx, dy)) {
				continue;
			}

			if (cell_matrix[dy][dx].isVisible()) {
				++count;
			}
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
	unsigned int xpos = asMatrixCoordinate(x);
	unsigned int ypos = asMatrixCoordinate(y);

	if (!coordinatesExist(xpos, ypos)) {
		return;
	}

	cell_matrix[ypos][xpos].setVisible(true);
}

bool CellContainer::coordinatesExist(int x, int y)
{
	if (y < 1 || y > static_cast<int>(cell_matrix.size())) {
		return false;
	}
	if (x < 1 || x > static_cast<int>(cell_matrix[y].size())) {
		return false;
	}
	return true;
}

unsigned int CellContainer::asMatrixCoordinate(int coord)
{
	return static_cast<unsigned int>((coord - (coord % 2)) / 2);
}

void CellContainer::addGlider(int x, int y)
{
	unsigned int xpos = asMatrixCoordinate(x) + 3;
	unsigned int ypos = asMatrixCoordinate(y) + 3;

	if (!coordinatesExist(xpos, ypos) || !coordinatesExist(xpos+2, ypos+2)) {
		return;
	}

	// Clear the glider area
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			cell_matrix[ypos+i][xpos+j].setVisible(false);
		}
	}

	// Top row
	cell_matrix[ypos][xpos+1].setVisible(true);

	// Middle row
	cell_matrix[ypos+1][xpos+2].setVisible(true);

	// Bottom row
	cell_matrix[ypos+2][xpos].setVisible(true);
	cell_matrix[ypos+2][xpos+1].setVisible(true);
	cell_matrix[ypos+2][xpos+2].setVisible(true);

	// Update the glider area
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			cell_matrix[ypos+i][xpos+j].update();
		}
	}
}
