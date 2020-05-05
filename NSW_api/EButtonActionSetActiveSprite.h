#pragma once
#include "NSW_api/EButtonAction.h"

class EButtonActionSetActiveSprite : public EButtonAction
{
public:
	EButtonActionSetActiveSprite();
	~EButtonActionSetActiveSprite();

	virtual void button_action(EButton* _b, float _d);
};