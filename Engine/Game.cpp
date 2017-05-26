/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	slider( RectF( Vec2( 350.0f,575.0f ),100.0f,20.0f ),1.0f,10.0f,5.0f )
{
}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = frameTimer.GetElapsedTime();
	while( elapsedTime > 0.0f )
	{
		const float delta = std::min( TIMESTEP,elapsedTime );
		UpdateModel( delta );
		elapsedTime -= delta;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel( float delta )
{
	while( !wnd.kbd.KeyIsEmpty() )
	{
		const Keyboard::Event e = wnd.kbd.ReadKey();
		if( e.IsPress() )
		{
			switch( e.GetCode() )
			{
			case VK_SPACE:
				paused = !paused;
				break;
			case VK_RIGHT:
				gol.StepForward();
				break;
			case VK_LEFT:
				gol.StepBackward();
				break;
			case VK_DELETE:
				gol.Clear();
				paused = true;
				break;
			}
		}
	}

	if( wnd.mouse.LeftIsPressed() )
	{
		auto pos = wnd.mouse.GetPos();
		if( gol.GetRect().Contains( pos ) )
		{
			gol.EditCell( pos,eraser );
		}
	}

	if( !paused )
	{
		stepTimer += delta;
		if( stepTimer >= stepPeriod )
		{
			stepTimer -= stepPeriod;
			gol.StepForward();
		}
	}

	slider.Update( wnd.mouse );
	stepPeriod = 1 / slider.GetValue();
}

void Game::ComposeFrame()
{
	gol.Draw( gfx );
	slider.Draw( gfx );
}
