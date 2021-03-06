#include "GOL.h"
#include <random>

GOL::GOL()
{
	std::random_device rd;
	std::mt19937 rng( rd() );
	std::bernoulli_distribution bDist( 0.5 );

	std::unique_ptr<BoardState> init = std::make_unique<BoardState>();
	for( bool& b : init->board )
	{
		b = bDist( rng );
	}

	states.push_front( std::move( init ) );
	iter = states.begin();
}

void GOL::StepForward()
{
	if( lookingBackward )
	{
		--iter;
		if( iter == states.begin() )
		{
			lookingBackward = false;
		}
	}
	else
	{
		auto next = std::make_unique<BoardState>();

		for( int yy = 0; yy < GRID_HEIGHT; ++yy )
		{
			for( int xx = 0; xx < GRID_WIDTH; ++xx )
			{
				int neighbours = 0;
				for( int i = -1; i <= 1; ++i )
				{
					for( int j = -1; j <= 1; ++j )
					{
						if( IsInsideBoard( xx + i,yy + j ) )
						{
							if( Cell( xx + i,yy + j ) )
							{
								++neighbours;
							}
						}
					}
				}

				if( Cell( xx,yy ) )
				{
					--neighbours;
				}

				if( Cell( xx,yy ) && neighbours < 2 )
				{
					next->board[GRID_WIDTH * yy + xx] = false;
				}
				else if( Cell( xx,yy ) && neighbours > 3 )
				{
					next->board[GRID_WIDTH * yy + xx] = false;
				}
				else if( !Cell( xx,yy ) && neighbours == 3 )
				{
					next->board[GRID_WIDTH * yy + xx] = true;
				}
				else
				{
					next->board[GRID_WIDTH * yy + xx] = Cell( xx,yy );
				}
			}
		}

		states.push_front( std::move( next ) );
		iter = states.begin();

		if( states.size() > MAX_HISTORY )
		{
			states.pop_back();
			iter = states.begin();
		}
	}
}

void GOL::StepBackward()
{
	if( ++iter == states.end() )
	{
		--iter;
	}
	else
	{
		lookingBackward = true;
	}
}

void GOL::EditCell( const Vei2& mousePos,bool eraser )
{
	const Vei2 cell = (mousePos - Vei2( GRID_X,GRID_Y )) / (CELL_SIZE + PADDING);
	assert( IsInsideBoard( cell.x,cell.y ) );
	Cell( cell.x,cell.y ) = !eraser;
}

void GOL::Draw( Graphics& gfx ) const
{
	const RectI rect = GetRect();
	gfx.FillRect( rect.GetExpanded( BORDER_THICKNESS + PADDING ),BORDER_COLOR );
	gfx.FillRect( rect.GetExpanded( PADDING ),BACK_COLOR );
	for( int yy = 0; yy < GRID_HEIGHT; ++yy )
	{
		for( int xx = 0; xx < GRID_WIDTH; ++xx )
		{
			if( Cell( xx,yy ) )
			{
				gfx.FillRectDim(
					GRID_X + xx * CELL_SIZE + xx * PADDING + PADDING / 2,
					GRID_Y + yy * CELL_SIZE + yy * PADDING + PADDING / 2,
					CELL_SIZE,
					CELL_SIZE,
					Colors::Yellow );
			}
		}
	}
}

RectI GOL::GetRect() const
{
	return RectI( Vei2( GRID_X,GRID_Y ),
		GRID_WIDTH * ( CELL_SIZE + PADDING ),
		GRID_HEIGHT * ( CELL_SIZE + PADDING ) );
}

void GOL::Clear()
{
	states.emplace_front( std::make_unique<BoardState>() );
	iter = states.begin();
}
