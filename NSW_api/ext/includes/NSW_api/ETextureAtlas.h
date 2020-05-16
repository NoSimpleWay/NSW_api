#pragma once
//#include 
#include "EGraphicCore.h"
#include <iostream>

class ETextureAtlas
{
public:
	unsigned int framebuffer;
	unsigned int colorbuffer;
	unsigned int rbo;

	float size_x;
	float size_y;

	bool free_space[1024][1024];

	bool can_place_here(int _x, int _y, int _w, int _h);

	static EGabarite* put_texture_to_atlas(std::string _name, ETextureAtlas* _ta);
	static void active_this_texture_atlas(ETextureAtlas* _ta, ETextureAtlas* _ta2, float _offset_x, float _offset_y, float _zoom);
	static void return_to_this_texture_atlas(ETextureAtlas* _ta);

	ETextureAtlas(int _x, int _y);
	~ETextureAtlas();
};