#pragma once
#include <string>
class EMath
{
public:
	static float clamp_value_float(float _v, float _min, float _max);
	static int clamp_value_int(int _v, int _min, int _max);


};

class EFile
{
	static int *data_array[];

	static void data_parser(std::string _s);
};