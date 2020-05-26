#include "EColor.h"

EColorCollection* EColor::COLOR_RED					= new EColorCollection(1.0f,	0.0f,	0.0f,	1.0f);
EColorCollection* EColor::COLOR_GREEN				= new EColorCollection(0.0f,	1.0f,	0.0f,	1.0f);
EColorCollection* EColor::COLOR_BLUE				= new EColorCollection(0.0f,	0.0f,	1.0f,	1.0f);

EColorCollection* EColor::COLOR_DARK_RED			= new EColorCollection(0.5f,	0.0f,	0.0f,	1.0f);
EColorCollection* EColor::COLOR_DARK_GREEN			= new EColorCollection(0.0f,	0.5f,	0.0f,	1.0f);
EColorCollection* EColor::COLOR_DARK_BLUE			= new EColorCollection(0.0f,	0.0f,	0.5f,	1.0f);

EColorCollection* EColor::COLOR_YELLOW				= new EColorCollection(1.0f,	1.0f,	0.0f,	1.0f);
EColorCollection* EColor::COLOR_ORANGE				= new EColorCollection(1.0f,	0.5f,	0.0f,	1.0f);
EColorCollection* EColor::COLOR_PINK				= new EColorCollection(1.0f,	0.33f,	1.0f,	1.0f);

EColorCollection* EColor::COLOR_WHITE				= new EColorCollection(1.0f,	1.0f,	1.0f,	1.0f);
EColorCollection* EColor::COLOR_BLACK				= new EColorCollection(0.0f,	0.0f,	0.0f,	1.0f);

EColorCollection* EColor::COLOR_LIGHT_GRAY			= new EColorCollection(0.75f,	0.75f,	0.75f,	1.0f);
EColorCollection* EColor::COLOR_GRAY				= new EColorCollection(0.5f,	0.5f,	0.5f,	1.0f);
EColorCollection* EColor::COLOR_DARK_GRAY			= new EColorCollection(0.25f,	0.25f,	0.25f,	1.0f);

EColorCollection* EColor::COLOR_LAZURE_SHADOW		= new EColorCollection(0.5f, 0.55f, 0.6f, 1.0);
EColorCollection* EColor::COLOR_SKY_AMBIENT			= new EColorCollection(1.0f, 0.9f, 0.8f, 1.0);

EColor::EColor(float _r, float _g, float _b, float _a)
{
	red		= _r;
	green	= _g;
	blue	= _b;
	alpha	= _a;
}

EColor::~EColor()
{
}

void EColor::set_color(float _r, float _g, float _b, float _a)
{
	red = _r;
	green = _g;
	blue = _b;
	alpha = _a;
}

void EColor::set_color(EColorCollection* _c)
{
	red = _c->color_red;
	green = _c->color_green;
	blue = _c->color_blue;
	alpha = _c->color_alpha;
}

void EColor::set_color_lum(EColorCollection* _c, float _lum)
{
	red = _c->color_red * _lum;
	green = _c->color_green * _lum;
	blue = _c->color_blue * _lum;
	alpha = _c->color_alpha;
}

void EColor::set_color_alpha(EColorCollection* _c, float _a)
{
	red = _c->color_red;
	green = _c->color_green;
	blue = _c->color_blue;
	alpha = _a;
}
