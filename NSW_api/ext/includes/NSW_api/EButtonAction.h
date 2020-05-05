#pragma once
#include <NSW_api\EButton.h>

class EButton;
class EButtonAction
{
public:
	virtual void button_action(EButton* _b, float _d);
};