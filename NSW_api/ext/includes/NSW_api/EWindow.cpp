#include "EWindow.h"

GLFWwindow* EWindow::main_window = NULL;

std::vector<EWindow*> EWindow::window_list;

ETextureAtlas* EWindow::default_texture_atlas;








unsigned int EWindow::transformLoc;

int EWindow::mouse_x = 0;
int EWindow::mouse_y = 0;

bool EWindow::LMB = false;
bool EWindow::RMB = false;

bool EWindow::button_pressed = false;
bool EWindow::button_right_pressed = false;
bool EWindow::button_backspace_released = true;
bool EWindow::is_active = true;

float EWindow::delete_button_hold_time = 0.0f;

char EWindow::last_inputed_char = NULL;

std::vector <float> EWindow::time_process_value;
std::vector <std::string> EWindow::time_process_name;

bool EWindow::system_button_release = true;

std::chrono::time_point<std::chrono::high_resolution_clock> EWindow::start, EWindow::stop;

//std::pair<float, std::string> EWindow::time_process;

void EWindow::default_update(float _d)
{
	for (int i = 0; i < button_list.size(); i++)
	{
		if (button_list.at(i)->need_remove)
		{
			button_list.erase(button_list.begin() + i);
		}
	}

	for (EButton* b : button_list)
	{
		if (b->is_active)
		{
			b->update(_d);
		}
	}

	for (EButton* b : default_button_list)
	{
		if (b->is_active)
		{
			b->update(_d);
		}
	}
}

void EWindow::update(float _d)
{
}

void EWindow::default_draw(float _d)
{
	if (have_bg)
	{
		EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 0.8f);
		EGraphicCore::batch->draw_gabarite(offset_x, offset_y, window_size_x, window_size_y, EGraphicCore::gabarite_white_pixel);
	}

	for (EButton* b : button_list)
	{
		if (b->is_active)
		{
			b->default_draw(EGraphicCore::batch);
		}
	}

	for (EButton* b : default_button_list)
	{
		if (b->is_active)
		{
			b->default_draw(EGraphicCore::batch);
		}
	}
}

void EWindow::draw(float _d)
{
}

void EWindow::default_resize_event()
{
	if (always_fullscreen)
	{
		window_size_x = EGraphicCore::SCR_WIDTH;
		window_size_y = EGraphicCore::SCR_HEIGHT;

		offset_x = 0;
		offset_y = 0;
	}
	else
	{
		if (align_x == Enums::PositionMode::LEFT) { offset_x = position_x; }
		if (align_x == Enums::PositionMode::MID) { offset_x = (EGraphicCore::SCR_WIDTH - window_size_x) / 2.0f + position_x; }
		if (align_x == Enums::PositionMode::RIGHT) { offset_x = (EGraphicCore::SCR_WIDTH - window_size_x) + position_x; }		
		
		if (align_x == Enums::PositionMode::DOWN) { offset_y = position_y; }
		if (align_x == Enums::PositionMode::MID) { offset_y = (EGraphicCore::SCR_HEIGHT - window_size_y) / 2.0f + position_y; }
		if (align_x == Enums::PositionMode::RIGHT) { offset_y = (EGraphicCore::SCR_HEIGHT - window_size_y) + position_y; }
	}
}

void EWindow::draw_interface(float _d)
{
}

void EWindow::add_time_process(std::string _name)
{
	stop = std::chrono::high_resolution_clock::now();

	time_process_value.push_back(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000.0f);
	time_process_name.push_back(_name);

	start = std::chrono::high_resolution_clock::now();
}

EWindow::EWindow()
{
	default_resize_event();
}

EWindow::~EWindow()
{
}

bool EWindow::is_overlap(EWindow* _w)
{

	if
	(
		(mouse_x >= _w->offset_x)
		&&
		(mouse_x <= _w->offset_x + _w->window_size_x)
		&&
		(mouse_y >= _w->offset_y)
		&&
		(mouse_y <= _w->offset_y + _w->window_size_y)
	)
	{
		return true;
	}

	return false;
}


