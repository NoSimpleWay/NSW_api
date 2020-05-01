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
