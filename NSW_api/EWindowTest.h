#include "NSW_api/EWindow.h"
#include "ECamera.h"
#include "EntityManager.h"

class EWindowTest : public EWindow
{
public:
	EWindowTest();
	~EWindowTest();

	bool time_process_active = true;

	void default_update(float _d);
	virtual void update(float _d);

	void default_draw(float _d);
	virtual void draw(float _d);

	virtual void draw_interface(float _d);

	Entity* link_to_player;

	ECamera* game_camera = new ECamera();

};