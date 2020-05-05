#pragma once
#include "NSW_api/EButton.h"

class EBA
{
public:
	EBA();
	~EBA();



	static void set_method(void (*function)());

	static void do_something();

	static void action_add_new_sprite(EButton* _b, float _d);
	static void action_select_sprite(EButton* _b, float _d);
	static void action_set_sprite_texture(EButton* _b, float _d);
	static void action_set_button_as_removed(EButton* _b, float _d);
	static void action_close_window(EButton* _b, float _d);
	
};