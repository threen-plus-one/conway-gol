#pragma once

#include "Mouse.h"
#include "Graphics.h"
#include "RectF.h"
#include "Vec2.h"

class Slider
{
	RectF rect;
	float minimum;
	float maximum;
	float value;

	float Clamp( float newValue )
	{
		if( newValue < minimum )
		{
			return minimum;
		}
		else if( newValue > maximum )
		{
			return maximum;
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