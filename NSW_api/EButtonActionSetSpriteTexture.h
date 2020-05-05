#pragma once
#include "NSW_api/EButtonAction.h"

class EButtonActionSetSpriteTexture : public EButtonAction
{
public:
	EButtonActionSetSpriteTexture();
	~EButtonActionSetSpriteTexture();

	virtual void button_action(EButton* _b, float _d);
};