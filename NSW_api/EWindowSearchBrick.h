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

	int search_mode;

	void update_search(std::string _text);

	enum SearchMode{ SEARCH_TEXTURE, SEARCH_ENTITY };

};