#pragma once

#include "Graphics.h"
#include <cassert>

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
		assert( IsInsideBoard( x,y ) );
		return board[ GRID_WIDTH * y + x ];
	}
	bool IsInsideBoard( int x,int y ) const
	{
		return
			x >= 0 &&
			x < GRID_WIDTH &&
			y >= 0 &&
			y < GRID_HEIGHT;
	}

public:
	GOL();

	void Step();
	void Draw( Graphics& gfx ) const;

	void Clear();
};