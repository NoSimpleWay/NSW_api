#include "EWindow.h"
#include "../../../EBA.h"

GLFWwindow* EWindow::main_window = NULL;

std::vector<EWindow*> EWindow::window_list;

ETextureAtlas* EWindow::default_texture_atlas;
ETextureAtlas* EWindow::shadow_FBO;
ETextureAtlas* EWindow::lightmap_FBO;
ETextureAtlas* EWindow::lightmap_FBO2;
ETextureAtlas* EWindow::lightmap_with_ambient;








unsigned int EWindow::transformLoc;

double EWindow::mouse_x = 0;
double EWindow::mouse_y = 0;

int EWindow::saved_pos_x = 0;
int EWindow::saved_pos_y = 0;

int EWindow::prev_mouse_x = 0;
int EWindow::prev_mouse_y = 0;

float EWindow::mouse_speed_x = 0.0f;
float EWindow::mouse_speed_y = 0.0f;

float EWindow::real_mouse_x;
float EWindow::real_mouse_y;

bool EWindow::LMB = false;
bool EWindow::RMB = false;

bool EWindow::button_pressed = false;
bool EWindow::button_main_group_pressed = false;

bool EWindow::button_right_pressed = false;
bool EWindow::button_backspace_released = true;


//bool EWindow::is_active = true;

float EWindow::delete_button_hold_time = 0.0f;

char EWindow::last_inputed_char = NULL;

int EWindow::time_process_rota_id = 0;

std::vector<EWindow::time_process_struct*> EWindow::tps_list;

bool EWindow::system_button_release = true;
double EWindow::scroll = 0;


std::chrono::time_point<std::chrono::high_resolution_clock> EWindow::start, EWindow::stop;

EWindowTest* EWindow::window_test;
EWindowEditor* EWindow::window_editor;
EWindowSearchBrick* EWindow::window_search_brick;
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
		
		if (align_y == Enums::PositionMode::DOWN) { offset_y = position_y; }
		if (align_y == Enums::PositionMode::MID) { offset_y = (EGraphicCore::SCR_HEIGHT - window_size_y) / 2.0f + position_y; }
		if (align_y == Enums::PositionMode::UP) { offset_y = (EGraphicCore::SCR_HEIGHT - window_size_y) + position_y; }
	}
}

void EWindow::default_draw_interface(float _d)
{

	EGraphicCore::batch->reinit();
	EGraphicCore::batch->draw_call();


	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f, -1.0f, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x, EGraphicCore::correction_y, 1));

	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	//סבנמס באעקונא
	EGraphicCore::batch->reset();

	for (EButton* b : button_list)
	{
		if (b->is_active)
		{
			b->default_draw(EGraphicCore::batch, _d);
			b->additional_draw(EGraphicCore::batch, _d);
		}
	}
	
	for (EButton* b : button_list)
	{
		if (b->is_active)
		{
			b->text_pass(EGraphicCore::batch);
		}
	}

	for (EButton* b : default_button_list)
	{
		if (b->is_active)
		{
			b->default_draw(EGraphicCore::batch, _d);
			b->additional_draw(EGraphicCore::batch, _d);
		}
	}

	for (EButton* b : default_button_list)
	{
		if (b->is_active)
		{
			b->text_pass(EGraphicCore::batch);
		}
	}
}

void EWindow::draw_interface(float _d)
{

}

void EWindow::add_time_process(std::string _name)
{
	//std::vector <float> tvec = new std::vector<float>(60, 0.0f);

	int id = -1;
	int tid = 0;
	for (time_process_struct* tps : tps_list)
	{
		if (tps->time_process_name == _name) { id = tid; break; }

		tid++;
	}

	stop = std::chrono::high_resolution_clock::now();
	

	if (id != -1)
	{
		tps_list.at(id)->time_process_name = _name;
		tps_list.at(id)->time_process_value.at(time_process_rota_id) = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000.0f;
	}
	else
	{
		time_process_struct* new_tps = new time_process_struct;

		tps_list.push_back(new_tps);

		for (int i = 0; i < 30; i++)
		{new_tps->time_process_value.push_back(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000.0f);}

		new_tps->time_process_name = _name;
	}

	start = std::chrono::high_resolution_clock::now();

}

void EWindow::push_cursor(float _x, float _y)
{
	SetCursorPos(real_mouse_x + _x, real_mouse_y + _y);

	mouse_x += _x;
	mouse_y += _y;

	real_mouse_x += _x;
	real_mouse_y += _y;
}

EWindow::EWindow()
{
	default_resize_event();

	EButton* but = new EButton(0.0f, 0.0f, 20.0f, 20.0f);
	but->master_window = this;
	but->position_mode_x = Enums::PositionMode::RIGHT;
	but->position_mode_y = Enums::PositionMode::UP;
	but->text = "X";
	but->action_on_left_click = &EBA::action_close_window;
	
	default_button_list.push_back(but);
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


