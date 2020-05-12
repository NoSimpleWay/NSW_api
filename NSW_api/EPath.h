#pragma once
class EPath
{
public:
	static int active_buffer;
	static int back_buffer;

	static const int PATH_SIZE = 40;
	static const int PATH_DIM = 250;
	static const short ENTITY_BLOCK_VALUE = 10;

	static short path[PATH_DIM][PATH_DIM][2];
	static bool block[PATH_DIM][PATH_DIM];
	static bool entity_block[PATH_DIM][PATH_DIM];

	static int phase;

	static int clamp_phase;

	static float cooldown;

	EPath();


};