#pragma once
#include <string>
class EMath
{
public:
	static float clamp_value_float(float _v, float _min, float _max);
	static int clamp_value_int(int _v, int _min, int _max);
	static float to_float(std::string _text);


};

class EFile
{
public:
	static std::string *data_array;
	static int array_size;

	static void data_parser(std::string _s);
	static int find_data_array_id(std::string _s);
};

class EString
{
public:
	static bool is_contain(std::string _text_source, std::string _text_value);
};