#include "GOL.h"
#include <random>

GOL::GOL()
{
	std::random_device rd;
	std::mt19937 rng( rd() );
	std::bernoulli_distribution bDist( 0.5 );

	for( bool& b : board )
	{
		b = bDist( rng );
	}
}

void GOL::Step()
{
	bool next[ GRID_WIDTH * GRID_HEIGHT ] = { false };

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
				next[ GRID_WIDTH * yy + xx ] = false;
			}
			else if( Cell( xx,yy ) && neighbours > 3 )
			{
				next[ GRID_WIDTH * yy + xx ] = false;
			}
			else if( !Cell( xx,yy ) && neighbours == 3 )
			{
				next[ GRID_WIDTH * yy + xx ] = true;
			}
			else
			{
				next[ GRID_WIDTH * yy + xx ] = Cell( xx,yy );
			}
		}
	}

	for( int i = 0; i < GRID_WIDTH * GRID_HEIGHT; ++i )
	{
		board[i] = next[i];
	}
}

void GOL::Draw( Graphics& gfx ) const
{
	const RectF rect = GetRect();
	gfx.FillRect( rect.GetExpanded( float( BORDER_THICKNESS + PADDING ) ),BORDER_COLOR );
	gfx.FillRect( rect.GetExpanded( float( PADDING ) ),BACK_COLOR );
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

RectF GOL::GetRect() const
{
	return RectF( Vec2( float( GRID_X ),float( GRID_Y ) ),
		float( GRID_WIDTH * ( CELL_SIZE + PADDING ) ),
		float( GRID_HEIGHT * ( CELL_SIZE + PADDING ) ) );
}

void GOL::Clear()
{
	for( bool& b : board )
	{
		b = false;
	}
}
