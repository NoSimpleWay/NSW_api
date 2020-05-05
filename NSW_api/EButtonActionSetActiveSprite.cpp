#include "EButtonActionSetActiveSprite.h"
#include "EWindowEditor.h"

EButtonActionSetActiveSprite::EButtonActionSetActiveSprite()
{
}

EButtonActionSetActiveSprite::~EButtonActionSetActiveSprite()
{
}

void EButtonActionSetActiveSprite::button_action(EButton* _b, float _d)
{
	EWindow::window_editor->sprite_button_list.at(EWindow::window_editor->selected_sprite_id)->rama_color->set_color (EColor::COLOR_BLACK);
	EWindow::window_editor->selected_sprite_id = _b->data_id;
	_b->rama_color->set_color (EColor::COLOR_ORANGE);
}
