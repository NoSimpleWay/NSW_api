#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION

#include <ctime>

#include "NSW_api/EWindow.h"
#include "EWindowTest.h"
#include "EWindowEditor.h"
#include "EWindowSearchBrick.h"

#include "NSW_api/EGraphicCore.h"
//#include "ETextureAtlas.h"


#include "NSW_api/Enums.h"
#include "NSW_api/EFont.h"
#include "EBA.h"

















static unsigned int transformLoc;

float delta_time;
float saved_time_for_delta;



void recalculate_correction();
void processInput(GLFWwindow* window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void recalculate_correction();
void processInput(GLFWwindow* window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_position_callback(GLFWwindow* window, double _x, double _y);
void char_input_callback(GLFWwindow* window, unsigned int _char);
//void load_texture(char const* _path, int _id);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main()
{


	srand(time(NULL));

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

// glfw window creation
// --------------------
	EWindow::main_window = glfwCreateWindow(EGraphicCore::SCR_WIDTH, EGraphicCore::SCR_HEIGHT, "Window name", NULL, NULL);

	if (EWindow::main_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(EWindow::main_window);

	glfwSetFramebufferSizeCallback(EWindow::main_window, framebuffer_size_callback);
	glfwSetScrollCallback(EWindow::main_window, scroll_callback);
	glfwSetMouseButtonCallback(EWindow::main_window, mouse_button_callback);
	glfwSetCursorPosCallback(EWindow::main_window, mouse_position_callback);
	glfwSetCharCallback(EWindow::main_window, char_input_callback);

	glfwSetInputMode(EWindow::main_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	//glfwSetMousePos(0, 0);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	EGraphicCore::ourShader = new Shader("data/5.1.transform.vs", "data/5.1.transform.fs");

	EGraphicCore::ourShader->use();
	glfwSwapInterval(1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, EGraphicCore::SCR_WIDTH, EGraphicCore::SCR_HEIGHT);
	recalculate_correction();

	//
	//batcher initiation
	EGraphicCore::batch = new Batcher();

	for (int i = 0; i < 5000; i++)
	{
		EGraphicCore::batch->fill_indices();
	}

	EGraphicCore::batch->init();
	//
	//

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glBlendEquation(GL_FUNC_ADD);
	//--------------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------------

	//cout << (int)01.35f << endl;
	glViewport(0, 0, EGraphicCore::SCR_WIDTH, EGraphicCore::SCR_HEIGHT);

	EWindow::default_texture_atlas = new ETextureAtlas(4096, 4096);

	EWindow::shadow_FBO = new ETextureAtlas(1920, 1080);

	EGraphicCore::load_texture("data/textures/white_pixel.png", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, EGraphicCore::texture[0]);
	EGraphicCore::ourShader->setInt("texture1", EGraphicCore::texture[0]);

	

	EWindowTest* wg = new EWindowTest();
	//EWindow::window_game = wg;
	EWindow::window_list.push_back(wg);
	EWindow::window_test = wg;
	wg->id = 0;

	EWindow::window_editor = new EWindowEditor();
	//EWindow::window_game = wg;
	EWindow::window_list.push_back(EWindow::window_editor);
	EWindow::window_editor->id = 1;
	EWindow::window_editor->always_fullscreen = true;
	EWindow::window_editor->have_bg = false;

	EWindow::window_search_brick = new EWindowSearchBrick();
	//EWindow::window_game = wg;
	EWindow::window_list.push_back(EWindow::window_search_brick);
	EWindow::window_search_brick->id = 2;
	EWindow::window_search_brick->is_active = false;

	
	//wg->init();


	//loading font

	for (EWindow* w : EWindow::window_list)
	{
		w->default_resize_event();
	}

	std::cout << "game window created" << std::endl;



	
	EGraphicCore::gabarite_white_pixel = ETextureAtlas::put_texture_to_atlas("data/textures/white_pixel.png", EWindow::default_texture_atlas);

	EGraphicCore::gabarite_white_pixel->x += 1 / 4096.0f;
	EGraphicCore::gabarite_white_pixel->y += 1 / 4096.0f;

	EGraphicCore::gabarite_white_pixel->x2 -= 1 / 4096.0f;
	EGraphicCore::gabarite_white_pixel->y2 -= 1 / 4096.0f;




	EGraphicCore::gabarite_wood_button_bg = ETextureAtlas::put_texture_to_atlas("data/textures/white_pixel.png", EWindow::default_texture_atlas);
	EGraphicCore::gabarite_wood_button_bg->x += 1 / 4096.0f;
	EGraphicCore::gabarite_wood_button_bg->y += 1 / 4096.0f;

	EGraphicCore::gabarite_wood_button_bg->x2 -= 1 / 4096.0f;
	EGraphicCore::gabarite_wood_button_bg->y2 -= 1 / 4096.0f;
	
	EFont* new_font = NULL;
	EGabarite* font_gabarite = ETextureAtlas::put_texture_to_atlas("data/font/franklin_0.png", EWindow::default_texture_atlas);
	new_font = new EFont("franklin", font_gabarite, false);
	EFont::active_font = new_font;
	EFont::font_list.push_back(new_font);

	//EGabarite* zzz = ETextureAtlas::put_texture_to_atlas("data/font/franklin_0.png", EWindow::shadow_FBO);

	EBA::action_load_map(NULL, 0.0f);
	EBA::action_load_entity_collection(NULL, 0.0f);

	while (!glfwWindowShouldClose(EWindow::main_window))
	{


		EWindow::time_process_name.clear();
		EWindow::time_process_value.clear();

		EWindow::stop = std::chrono::high_resolution_clock::now();
		EWindow::start = std::chrono::high_resolution_clock::now();
		
		EWindow::add_time_process("Begin");

		clock_t time = clock();
		delta_time = (time - saved_time_for_delta) / 1000.0;
		saved_time_for_delta = time;

		delta_time /= 1.0f;//

		if (delta_time > 0.5f) { delta_time = 0.5f; }


		POINT cursorPos;
		GetCursorPos(&cursorPos);

		EWindow::mouse_speed_x = cursorPos.x - EWindow::prev_mouse_x;
		EWindow::mouse_speed_y = -(cursorPos.y - EWindow::prev_mouse_y);

		EWindow::real_mouse_x = cursorPos.x;
		EWindow::real_mouse_y = cursorPos.y;

		EWindow::prev_mouse_x = cursorPos.x;
		EWindow::prev_mouse_y = cursorPos.y;

		EWindow::scroll = 0;

		glfwPollEvents();




		//очищаем графический буфер и подготавливаем трансформацию
		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glClearColor(0.4f, 0.5f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

		EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1, -1, 0.0f));
		EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x, EGraphicCore::correction_y, 1));

		transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

		//сброс батчера
		EGraphicCore::batch->reset();



		EButton::top_window_id = -1;

		if (!EWindow::LMB) { EWindow::button_pressed = false; }
		if (!EWindow::RMB) { EWindow::button_right_pressed = false; }

		if (!EWindow::button_backspace_released)
		{
			EWindow::delete_button_hold_time += delta_time;
		}

		if
		(
			(glfwGetKey(EWindow::main_window, GLFW_KEY_BACKSPACE) == GLFW_RELEASE)
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_DELETE) == GLFW_RELEASE)
		)
		{
			EWindow::button_backspace_released = true;

			EWindow::delete_button_hold_time = 0;

		}

		if
		(
			(glfwGetKey(EWindow::main_window, GLFW_KEY_E) == GLFW_RELEASE)
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_V) == GLFW_RELEASE)
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_DELETE) == GLFW_RELEASE)
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_Z) == GLFW_RELEASE)
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_COMMA) == GLFW_RELEASE)
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_PERIOD) == GLFW_RELEASE)
		)
		{
			EWindow::button_main_group_pressed = false;
		}

		EButton::top_window_id = -1;
		for (int i = 0; i < EWindow::window_list.size(); i++)
		{
			if (
				(EWindow::is_overlap(EWindow::window_list.at(i)))
				&&
				(EWindow::window_list.at(i)->is_active)
				)
			{
				EButton::top_window_id = i;
			}
		}

				//update windows
		for (EWindow* w : EWindow::window_list)
		if (w->is_active)
		{
			w->default_update(delta_time);
			w->update(delta_time);

			for (EButton* b : w->button_list)
			if (b->is_active)
			{
				b->update(delta_time);
				b->update_additional(delta_time);
			}
		}

		for (EWindow* w : EWindow::window_list)
		if (w->is_active)
		{
			w->default_draw(delta_time);
			w->draw(delta_time);

			w->default_draw_interface(delta_time);
			w->draw_interface(delta_time);
		}


		EGraphicCore::batch->reinit();
		EGraphicCore::batch->draw_call();

		glfwSwapBuffers(EWindow::main_window);



		processInput(EWindow::main_window);

		EWindow::last_inputed_char = NULL;


	}

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{//
	glViewport(0, 0, width, height);
	glfwGetWindowSize(window, &EGraphicCore::SCR_WIDTH, &EGraphicCore::SCR_HEIGHT);

	std::cout << "Resize event width:" << width << " height: " << height << std::endl;

	recalculate_correction();
}

void recalculate_correction()
{
	if ((EGraphicCore::SCR_WIDTH > 100) && (EGraphicCore::SCR_HEIGHT > 100))
	{

		EGraphicCore::correction_x = 1.0 / EGraphicCore::SCR_WIDTH * 2.0;
		EGraphicCore::correction_y = 1.0 / EGraphicCore::SCR_HEIGHT * 2.0;

		//std::cout << "helper correction_x: " << correction_x << " correction_y: " << correction_y << std::endl;
	}

	for (EWindow* w : EWindow::window_list)
	{
		w->default_resize_event();
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	EWindow::scroll = yoffset;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//if () 00:13:53 27.11.2019
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		EWindow::LMB = true;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		EWindow::LMB = false;
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		EWindow::RMB = true;
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		EWindow::RMB = false;
	}
}

void mouse_position_callback(GLFWwindow* window, double _x, double _y)
{


	EWindow::mouse_x = _x;
	EWindow::mouse_y = EGraphicCore::SCR_HEIGHT - _y;



}

void char_input_callback(GLFWwindow* window, unsigned int _char)
{
	EWindow::last_inputed_char = _char;
}

void processInput(GLFWwindow* window)
{



	/*
	if ((glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS))
	{
		for (Entity* e : EWindow::window_game->entity_list)
		{
			*e->position_x = (rand() % 1000) + 55.0f;
			*e->position_y = (rand() % 1000) + 55.0f;
		}
	}*/

	/*
	if ((glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS))
	{
		for (int i = 0; i < PATH_MATRIX_ARRAY_SIZE; i++)
		for (int j = 0; j < PATH_MATRIX_ARRAY_SIZE; j++)
			{

				if (rand() % 5 == 0)
				{
					EWindow::window_game->unwalk_matrix[j][i][0] = true;
					EWindow::window_game->unwalk_matrix[j][i][1] = true;
				}
				else
				{
					EWindow::window_game->unwalk_matrix[j][i][0] = false;
					EWindow::window_game->unwalk_matrix[j][i][1] = false;
				}

				EWindow::window_game->path_matrix[j][i][0] = 99;
				EWindow::window_game->path_matrix[j][i][1] = 99;

				EWindow::window_game->blocked_by_entity[j][i][0] = false;
				EWindow::window_game->blocked_by_entity[j][i][1] = false;
			}
	}*/
}



