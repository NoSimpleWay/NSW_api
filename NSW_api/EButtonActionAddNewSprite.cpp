#include "EButtonActionAddNewSprite.h"
#include "EWindowEditor.h"



EButtonActionAddNewSprite::EButtonActionAddNewSprite()
{
}

EButtonActionAddNewSprite::~EButtonActionAddNewSprite()
{
}

void EButtonActionAddNewSprite::button_action(EButton* _b, float _d)
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
