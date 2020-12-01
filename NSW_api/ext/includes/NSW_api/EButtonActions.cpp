#pragma once
#include "EButtonActions.h"

	void EButtonActions::action_close_window(EButton* _b, float _d)
	{
		_b->master_window->is_active = false;
	}

	void EButtonActions::action_set_constant_bool_to_address(EButton* _b, float _d)
	{
		*_b->target_address_for_bool = *_b->target_value_for_bool;
	}

