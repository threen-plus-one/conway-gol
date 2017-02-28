#include "Slider.h"

Slider::Slider( const RectF& rect_in,float min_in,float max_in,float startValue )
	:
	rect( rect_in ),
	minimum( min_in ),
	maximum( max_in ),
	value( startValue )
{
}

void Slider::Update( const Mouse& mouse )
{
	if( mouse.LeftIsPressed() )
	{
		const Vec2 mousePos = { float( mouse.GetPosX() ),float( mouse.GetPosY() ) };
		if( rect.Contains( mousePos ) )
		{
			value = Clamp( mousePos.x - rect.left + minimum );
		}
	}
}

float Slider::GetValue() const
{
	return value;
}

void Slider::Draw( Graphics& gfx ) const
{
	const float width = rect.right - rect.left;
	const float sliderX = (value - minimum) / (maximum - minimum) * width + rect.left - 5.0f;
	gfx.DrawRect( rect,Colors::White );
	gfx.FillRect(
		int( sliderX ),
		int( rect.top ),
		int( sliderX + 10.0f ),
		int( rect.bottom ),
		Colors::White );
}
