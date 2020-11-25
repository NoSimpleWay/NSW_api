#include "EGabarite.h"

EGabarite::EGabarite(std::string _name, float _x, float _y, float _size_x, float _size_y)
{
	name = _name;

	*x = _x + 0.00001f;
	*y = _y + 0.00001f;

	*uv_size_x = _size_x - 0.00002;
	*uv_size_y = _size_y - 0.00002;

	*x2 = _x + _size_x - 0.00001f;
	*y2 = _y + _size_y - 0.00001f;

	*size_x = round(*uv_size_x * 4096.0f);
	*size_y = round(*uv_size_y * 4096.0f);
}

EGabarite::~EGabarite()
{
	delete x;
	delete y;
	delete uv_size_x;
	delete uv_size_y;
	delete x2;
	delete y2;
	delete size_x;
	delete size_y;
}
