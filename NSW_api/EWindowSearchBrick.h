#include "NSW_api/EWindow.h"

class EWindowSearchBrick : public EWindow
{
public:
	EWindowSearchBrick();
	~EWindowSearchBrick();

	EButton* link_to_input;

	std::vector<EButton*> brick_button;

	virtual void update(float _d);
	virtual void draw(float _d);
	virtual void draw_interface(float _d);



};