#pragma once
class EPath
{
public:
	static int active_buffer;
	static int back_buffer;

	static const int PATH_SIZE = 50;
	static const int PATH_DIM = 50;

	static short path[PATH_DIM][PATH_DIM][2];
	static short block[PATH_DIM][PATH_DIM];

	static int phase;

	static int clamp_phase;

	EPath();


};