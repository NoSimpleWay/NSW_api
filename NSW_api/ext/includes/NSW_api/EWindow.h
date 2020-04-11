#pragma once



#include <glad/glad.h>
#include <GLFW/glfw3.h>
//glm::mat4 matrix_transform;

#include "NSW_api/Batcher.h"
#include <vector>
#include "NSW_api/EFont.h"



#include <iostream>
#include <chrono>

#include "NSW_api/ETextureAtlas.h"
#include "NSW_api/EButton.h"

#include "NSW_api/EUtils.h"

class EButton;
class EWindow
{
public:
	void default_update(float _d);
	virtual void update(float _d);

	void default_draw(float _d);
	virtual void draw(float _d);

	void default_resize_event();


	virtual void draw_interface(float _d);

	void add_time_process(std::string _name);

	static GLFWwindow* main_window;

	static unsigned int transformLoc;

	float offset_x = 0;
	float offset_y = 0;

	float position_x = 0;
	float position_y = 0;
	
	float window_size_x = 100.0f;
	float window_size_y = 100.0f;

	static int mouse_x;
	static int mouse_y;

	static bool LMB;
	static bool RMB;

	static bool system_button_release;

	//static std::pair<float, std::string> time_process;

	static std::vector<float> time_process_value;
	static std::vector < std::string > time_process_name;

	static std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;

	EWindow();
	~EWindow();

	static Batcher* batch;
	static std::vector<EWindow*> window_list;
	static float delete_button_hold_time;

	static ETextureAtlas* default_texture_atlas;

	static bool button_pressed;
	static bool button_right_pressed;
	static bool button_backspace_released;
	static bool is_active;
	int id = 0;

	static bool is_overlap(EWindow* _w);

	static char last_inputed_char;

	std::vector <EButton*> button_list;
	std::vector <EButton*> default_button_list;

	bool always_fullscreen;
	bool have_bg = false;

	int align_x;
	int align_y;


};