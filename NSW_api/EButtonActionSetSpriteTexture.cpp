#include "EButtonActionSetSpriteTexture.h"
#include "EWindowTest.h"
#include "EWindowEditor.h"

EButtonActionSetSpriteTexture::EButtonActionSetSpriteTexture()
{
}

EButtonActionSetSpriteTexture::~EButtonActionSetSpriteTexture()
{
}

void EButtonActionSetSpriteTexture::button_action(EButton* _b, float _d)
{
	EWindow::window_test->link_to_player->sprite_list.at(EWindow::window_editor->selected_sprite_id)->gabarite.at(0) = _b->gabarite;
}
