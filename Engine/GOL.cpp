#include "GOL.h"
#include <random>

GOL::GOL()
{
	std::random_device rd;
	std::mt19937 rng( rd() );
	std::bernoulli_distribution bDist( 0.1 );

	for( bool& b : board )
	{
		b = bDist( rng );
	}
}

void GOL::Update( float delta )
{
}

void GOL::Draw( Graphics& gfx ) const
{
	for( int yy = 0; yy < GRID_HEIGHT; ++yy )
	{
		for( int xx = 0; xx < GRID_WIDTH; ++xx )
		{
			if( Cell( xx,yy ) )
			{
				gfx.FillRectDim(
					GRID_X + xx * CELL_SIZE + xx * PADDING,
					GRID_Y + yy * CELL_SIZE + yy * PADDING,
					CELL_SIZE,
					CELL_SIZE,
					Colors::Yellow );
			}
		}
	}
}
