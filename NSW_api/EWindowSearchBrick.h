#include "NSW_api/EWindow.h"

class EWindowSearchBrick : public EWindow
{
public:
	EWindowSearchBrick();
	~EWindowSearchBrick();

	std::vector<EGabarite*> list_of_textures;
	std::vector < std::string > list_of_textures_names;

	EButton* link_to_input;

	std::vector<EButton*> brick_button;

	virtual void update(float _d);
	virtual void draw(float _d);
	virtual void draw_interface(float _d);

	int search_mode = 0;

	void update_search(EButton* _b);

	enum SearchMode{ SEARCH_TEXTURE, SEARCH_ENTITY };

};