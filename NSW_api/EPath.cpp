#include "EPath.h"

int EPath::active_buffer = 0;
int EPath::back_buffer = 1;
int EPath::phase = 0;
int EPath::clamp_phase = 0;

short EPath::path[PATH_DIM][PATH_DIM][2];
short EPath::block[PATH_DIM][PATH_DIM];

EPath::EPath()
{

}
