#pragma once
#include "EColorCollection.h"

class EColor
{
public:

	float red;
	float green;
	float blue;
	float alpha;

	EColor(float _r, float _g, float _b, float _a);
	~EColor();

	void set_color(float _r, float _g, float _b, float _a);
	void set_color(EColorCollection* _c);
	void set_color_lum(EColorCollection* _c, float _lum);
	void set_color_alpha(EColorCollection* _c, float _lum);

	static EColorCollection* COLOR_RED;
	static EColorCollection* COLOR_GREEN;
	static EColorCollection* COLOR_BLUE;

	static EColorCollection* COLOR_DARK_RED;
	static EColorCollection* COLOR_DARK_GREEN;
	static EColorCollection* COLOR_DARK_BLUE;

	static EColorCollection* COLOR_YELLOW;
	static EColorCollection* COLOR_ORANGE;
	static EColorCollection* COLOR_PINK;

	static EColorCollection* COLOR_WHITE;
	static EColorCollection* COLOR_BLACK;

	static EColorCollection* COLOR_LIGHT_GRAY;
	static EColorCollection* COLOR_GRAY;
	static EColorCollection* COLOR_DARK_GRAY;

	static EColorCollection* COLOR_LAZURE_SHADOW;
	static EColorCollection* COLOR_SKY_AMBIENT;


};