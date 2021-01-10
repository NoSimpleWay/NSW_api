#include "EPath.h"

int EPath::active_buffer = 0;
int EPath::back_buffer = 1;
int EPath::phase = 0;
int EPath::clamp_phase = 0;

float EPath::cooldown = 0.02f;

short EPath::path[PATH_DIM][PATH_DIM][2];
bool EPath::block[PATH_DIM][PATH_DIM];
bool EPath::shadow_block[PATH_DIM][PATH_DIM];
bool EPath::entity_block[PATH_DIM][PATH_DIM];

EPath::EPath()
{

}
