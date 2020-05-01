#pragma once
class EMath
{
public:
	static float clamp_value_float(float _v, float _min, float _max);
	static int clamp_value_int(int _v, int _min, int _max);
};