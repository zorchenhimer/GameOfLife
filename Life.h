#ifndef __LIFE_H_
#define __LIFE_H_

#include "Globals.h"

#include <stdlib.h>
#include <time.h>

#define GRID_WIDTH 1280
#define GRID_HEIGHT 720

class Life {
public:
	bool **WorldGrid;
	Life();
	void update();
private:
	bool **tempgrid;
	int countNeighbors(int x, int y);
};

#endif