#include "Slider.h"

#include <cassert>

Slider::Slider( const RectF& rect_in,float min_in,float max_in,float startValue )
	:
	rect( rect_in.GetExpanded( -RECT_SHRINK ) ),
	minimum( min_in ),
	maximum( max_in )
{
	assert( startValue >= minimum && startValue <= maximum );
	sliderX =
		(startValue - minimum) / (maximum - minimum)
		* (rect.right - rect.left - SLIDER_WIDTH) + rect.left;
}

void Slider::Update( const Mouse& mouse )
{
	if( mouse.LeftIsPressed() )
	{
		const Vec2 mousePos = { float( mouse.GetPosX() ),float( mouse.GetPosY() ) };
		if( rect.Contains( mousePos ) )
		{
			sliderX = Clamp( mousePos.x );
		}
	}
}

float Slider::GetValue() const
{
	const float posAlongSlider = sliderX - rect.left;
	const float width = rect.right - rect.left;
	const float range = maximum - minimum;
	const float value = posAlongSlider / width * range + minimum;
	assert( value >= minimum && value <= maximum );
	return value;
}

void Slider::Draw( Graphics& gfx ) const
{
	const RectF sliderRect( sliderX,sliderX + SLIDER_WIDTH,rect.top,rect.bottom );
	gfx.DrawRect( rect,Colors::White );
	gfx.FillRect( sliderRect.GetExpanded( RECT_SHRINK ),Colors::White );
}
