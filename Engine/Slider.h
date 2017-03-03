#pragma once

#include "Mouse.h"
#include "Graphics.h"
#include "RectF.h"
#include "Vec2.h"

class Slider
{
	static constexpr float SLIDER_WIDTH = 10.0f;
	static constexpr float RECT_SHRINK = 2.0f;
	RectF rect;
	float sliderX;
	float minimum;
	float maximum;

	float Clamp( float newValue )
	{
		if( newValue < rect.left )
		{
			return rect.left;
		}
		else if( newValue > rect.right - SLIDER_WIDTH )
		{
			return rect.right - SLIDER_WIDTH;
		}
		else
		{
			return newValue;
		}
	}

public:
	Slider( const RectF& rect,float minimum,float maximum,float startValue );
	void Update( const Mouse& mouse );
	float GetValue() const;

	void Draw( Graphics& gfx ) const;
};