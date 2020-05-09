#include "NSW_api/EUtils.h"
#include <iostream>

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


std::string*EFile::data_array = new std::string[1];
int EFile::array_size = 0;

void EFile::data_parser(std::string _s)
{

	
	array_size = 1;
	std::string subdata = "";
	int dim = 0;

	for (int i = 0; i < _s.size(); i++)
	{
		if (_s[i] == '\t') { array_size++; }
	}

	if (array_size > 0)
	{
		data_array = new std::string[array_size];

		for (int i = 0; i < _s.length(); i++)
		{
			if ((_s.at(i) == '\t') || (i + 1 == _s.length()))
			{
				if (i + 1 == _s.length()) { subdata += _s.at(i); }

				data_array[dim] = subdata;

				//std::cout << "_______subdata [" << data_array[dim] << "] added to index " <<  std::endl << std::endl;

				subdata = "";
				dim++;
			}
			else
			{

				subdata += _s.at(i);

				//std::cout << "SUBATA:" << subdata << std::endl;
			}
		}
	}
}

int EFile::find_data_array_id(std::string _s)
{

	return 0;
}

bool EString::is_contain(std::string _text_source, std::string _text_value)
{
	if (_text_source.find(_text_value) != std::string::npos) {return true;}

	return false;
}
