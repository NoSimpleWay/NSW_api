#include "EBA.h"
#include <iostream>
#include "EntityManager.h"

#include "EWindowTest.h"
#include "EWindowEditor.h"
#include "EWindowSearchBrick.h"

void (*foo)();

EBA::EBA()
{
}

EBA::~EBA()
{
}







void EBA::set_method(void(*function)())
{
	foo = function;

	foo();

	//function();
}

void EBA::do_something()
{
}

void EBA::action_add_new_sprite(EButton* _b, float _d)
{
	ESprite* spr = new ESprite();

	spr->gabarite.push_back(ETextureAtlas::put_texture_to_atlas("data/textures/white_pixel.png", EWindow::default_texture_atlas));
	spr->offset_x.push_back(0.0f);
	spr->offset_y.push_back(0.0f);

	EWindow::window_editor->selected_entity->sprite_list.insert
	(
		EWindow::window_editor->selected_entity->sprite_list.begin() + EWindow::window_editor->selected_sprite_id,
		spr
	);
}

void EBA::action_select_sprite(EButton* _b, float _d)
{
	EWindow::window_editor->sprite_button_list.at(EWindow::window_editor->selected_sprite_id)->rama_color->set_color(EColor::COLOR_BLACK);
	EWindow::window_editor->selected_sprite_id = _b->data_id;
	_b->rama_color->set_color(EColor::COLOR_ORANGE);

	EWindow::window_search_brick->is_active = true;
}

void EBA::action_set_sprite_texture(EButton* _b, float _d)
{
	EWindow::window_test->link_to_player->sprite_list.at(EWindow::window_editor->selected_sprite_id)->gabarite.at(0) = _b->gabarite;
}

void EBA::action_set_button_as_removed(EButton* _b, float _d)
{
	_b->need_remove = true;
}

void EBA::action_close_window(EButton* _b, float _d)
{
	_b->master_window->is_active = false;

	//_b->master_window->window_size_x *= 0.9f;
}

/*
void EBA::action_add_new_sprite()
{
}
*/
