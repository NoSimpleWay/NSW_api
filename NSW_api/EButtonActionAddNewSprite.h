#pragma once
#include "NSW_api/EButtonAction.h"

class EButtonActionAddNewSprite : public EButtonAction
{
public:
	EButtonActionAddNewSprite();
	~EButtonActionAddNewSprite();

	virtual void button_action(EButton* _b, float _d);


};