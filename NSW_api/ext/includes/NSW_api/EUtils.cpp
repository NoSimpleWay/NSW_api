#include "NSW_api/EUtils.h"

float EMath::clamp_value_float(float _v, float _min, float _max)
{
	if (_v < _min) { return _min; }
	if (_v > _max) { return _max; }
	return _v;


}

int EMath::clamp_value_int(int _v, int _min, int _max)
{
	if (_v < _min) { return _min; }
	if (_v > _max) { return _max; }
	return _v;
}


int *EFile::data_array[] = NULL;

void EFile::data_parser(std::string _s)
{
	int array_size = 0;

	for (int i = 0; i < _s.size(); i++)
	{
		if (_s[i] == '\t') { array_size++; }
	}

	if (array_size > 0)
	{*data_array = new int[array_size];}
}
