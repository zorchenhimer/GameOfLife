#include "Life.h"
#include <random>

Life::Life() {
	std::random_device rd;
	std::mt19937_64 gen(rd());

	this->WorldGrid = new bool*[GRID_HEIGHT];
	for (int i = 0; i < GRID_HEIGHT; i++) {
		this->WorldGrid[i] = new bool[GRID_WIDTH];
	}

	this->tempgrid = new bool*[GRID_HEIGHT];
	for (int i = 0; i < GRID_HEIGHT; i++) {
		this->tempgrid[i] = new bool[GRID_WIDTH];
	}

	for (int x = 0; x < GRID_HEIGHT; x++) {
		for (int y = 0; y < GRID_WIDTH; y++) {
			int r = gen();
			if (r % 10 == false)
				this->WorldGrid[x][y] = true;
			else
				this->WorldGrid[x][y] = false;
		}
	}
}

void Life::update() {
	// Calculate states for each cell
	for (int x = 0; x < GRID_HEIGHT; x++) {
		for (int y = 0; y < GRID_WIDTH; y++) {
			int neighbors = this->countNeighbors(x, y);

			if (neighbors < 2 || neighbors > 3)
				this->tempgrid[x][y] = false;
			else if (neighbors == 3 && this->WorldGrid[x][y] == false)
				tempgrid[x][y] = true;
			else if ((neighbors == 2 || neighbors == 3) && this->WorldGrid[x][y] == true)
				tempgrid[x][y] = true;
		}
	}

	// Apply states for each cell
	for (int x = 0; x < GRID_HEIGHT; x++) {
		for (int y = 0; y < GRID_WIDTH; y++) {
			this->WorldGrid[x][y] = tempgrid[x][y];
			if (y == GRID_WIDTH - 1)
				continue;
		}
	}
}

int Life::countNeighbors(int x, int y) {
	int neighbors = 0;

	/*
	 *  1 2 3
	 *  4 X 5
	 *  6 7 8
	 */

	int wrapx = x;
	int wrapy = y;

	if (x == 0)
		wrapx = GRID_HEIGHT - 1;
	else if (x == GRID_HEIGHT)
		wrapx = 0;

	if (y == 0)
		wrapy = GRID_WIDTH - 1;
	else if (y == GRID_WIDTH)
		wrapy = 0;

	// 1, 4, 6
	if (x > 0) {
		// 4
		if (this->WorldGrid[(x-1)][y] == true)
			neighbors++;
		// 1
		if (y > 0 && this->WorldGrid[(x-1)][(y-1)] == true)
			neighbors++;
		// 6
		if (y < GRID_WIDTH - 1 && this->WorldGrid[(x-1)][(y+1)] == true)
			neighbors++;
	} else {
		// 4; wrap around
		if (this->WorldGrid[wrapx][y] == true)
			neighbors++;

		// 1; wrap around
		if (y > 0 && this->WorldGrid[wrapx][y-1])
			neighbors++;
		else if (y == 0 && this->WorldGrid[wrapx][wrapy])
			neighbors++;
		
		// 6; wrap around
		if (y < GRID_WIDTH - 1 && this->WorldGrid[wrapx][y+1])
			neighbors++;
		else if (y == GRID_WIDTH && this->WorldGrid[wrapx][wrapy])
			neighbors++;
	}

	// 3, 5, 8
	if (x < GRID_HEIGHT - 1) {
		// 5
		if ((this->WorldGrid[(x+1)][y]) == true)
			neighbors++;
		// 3
		if (y > 0 && this->WorldGrid[(x+1)][(y-1)] == true)
			neighbors++;
		// 8
		if (y < GRID_WIDTH - 1 && this->WorldGrid[(x+1)][(y+1)] == true)
			neighbors++;
	} else {
		// 5; wrap around
		if (this->WorldGrid[wrapx][y] == true)
			neighbors++;
		
		// 3; wrap around
		if( y > 0 && this->WorldGrid[wrapx][y-1])
			neighbors++;
		else if (y == 0 && this->WorldGrid[wrapx][wrapy])
			neighbors++;

		// 8; wrap around
		if (y < GRID_WIDTH - 1 && this->WorldGrid[wrapx][y+1])
			neighbors++;
		else if (y == GRID_WIDTH && this->WorldGrid[wrapx][wrapy])
			neighbors++;
	}

	// 2
	if (y > 0 && this->WorldGrid[x][(y-1)] == true)
		neighbors++;
	else if (y == 0 && this->WorldGrid[x][wrapy])
		neighbors++;

	// 7
	if (y < GRID_WIDTH - 1 && this->WorldGrid[x][(y+1)] == true)
		neighbors++;
	else if (y == GRID_WIDTH && this->WorldGrid[x][wrapy])
		neighbors++;

	return neighbors;
}