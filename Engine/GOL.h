#pragma once

#include "Graphics.h"
#include <cassert>
#include <memory>
#include <list>

/*
 * Conway's Game of Life
 */
class GOL
{
private:
	static constexpr int GRID_X = 150;
	static constexpr int GRID_Y = 50;
	static constexpr int GRID_WIDTH = 50;
	static constexpr int GRID_HEIGHT = 50;
	static constexpr int CELL_SIZE = 8;
	static constexpr int PADDING = 2;
	static constexpr int BORDER_THICKNESS = 10;
	static constexpr int MAX_HISTORY = 50;

	static constexpr Color BACK_COLOR = { 14,15,16 };
	static constexpr Color BORDER_COLOR = Colors::Blue;

	struct BoardState
	{
		bool board[ GRID_WIDTH * GRID_HEIGHT ] = { false };
	};
	std::list< std::unique_ptr<BoardState> > states;
	std::list< std::unique_ptr<BoardState> >::iterator iter;
	bool lookingBackward = false;

	bool Cell( int x,int y ) const
	{
		assert( IsInsideBoard( x,y ) );
		return (*iter)->board[ GRID_WIDTH * y + x ];
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

	void StepForward();
	void StepBackward();
	void Draw( Graphics& gfx ) const;

	RectF GetRect() const;

	void Clear();
};