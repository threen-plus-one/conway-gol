#pragma once

#include "Graphics.h"

/*
 * Conway's Game of Life
 */
class GOL
{
	static constexpr int GRID_X = 150;
	static constexpr int GRID_Y = 50;
	static constexpr int GRID_WIDTH = 50;
	static constexpr int GRID_HEIGHT = 50;
	static constexpr int CELL_SIZE = 8;
	static constexpr int PADDING = 2;

	bool board[ GRID_WIDTH * GRID_HEIGHT ] = { false };

	bool Cell( int x,int y ) const
	{
		return board[ GRID_WIDTH * (y % GRID_HEIGHT) + (x % GRID_WIDTH) ];
	}

public:
	GOL();

	void Step();
	void Draw( Graphics& gfx ) const;
};