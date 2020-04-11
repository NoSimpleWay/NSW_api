#include "NSW_api/EWindow.h"
#include "ECamera.h"

class EWindowTest : public EWindow
{
public:
	EWindowTest();
	~EWindowTest();

	void default_update(float _d);
	virtual void update(float _d);

	void default_draw(float _d);
	virtual void draw(float _d);

	virtual void draw_interface(float _d);

	ECamera* game_camera = new ECamera();

};