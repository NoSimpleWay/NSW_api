#pragma once

#define logger(_a_) std::cout << _a_ << std::endl

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION

class EFont;
class EButton;

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

#include <direct.h>
#include <iostream>
#include <chrono>


#include <windows.h>


#include <string>
#include <ctime>
#include <vector>

//main opengl library
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <learnopengl/shader_s.h>

//////

#include "NSW_api/Enums.h"
#include "EButtonActions.h"
#include "NSW_api/EColorCollection.h"
#include "NSW_api/EColor.h"
#include "NSW_api/EGabarite.h"

#include "NSW_api/Batcher.h"

#include "NSW_api/EUtils.h"

#include "NSW_api/EGraphicCore.h"
#include "NSW_api/ETextureAtlas.h"
#include "NSW_api/EWindow.h"


#include "NSW_api/EFont.h"


#include "NSW_api/EWindow.h"


#include "NSW_api/EGraphicCore.h"
//#include "ETextureAtlas.h"


#include <windows.h>
#include <stb_image.h>

 














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



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{//
	//width = round(width / 2.0f) * 2;
	//height = round(height / 2.0f) * 2;
	glfwSetWindowSize(EWindow::main_window, width, height);

	glViewport(0, 0, width, height);
	glfwGetWindowSize(window, &EGraphicCore::SCR_WIDTH, &EGraphicCore::SCR_HEIGHT);


	std::cout << "Resize event width:" << EGraphicCore::SCR_WIDTH << " height: " << EGraphicCore::SCR_HEIGHT << std::endl;

	recalculate_correction();
}

void recalculate_correction()
{
	if ((EGraphicCore::SCR_WIDTH > 100) && (EGraphicCore::SCR_HEIGHT > 100))
	{

		EGraphicCore::correction_x = 1.0f / EGraphicCore::SCR_WIDTH * 2.0f;
		EGraphicCore::correction_y = 1.0f / EGraphicCore::SCR_HEIGHT * 2.0f;

		//std::cout << "helper correction_x: " << correction_x << " correction_y: " << correction_y << std::endl;
	}

	for (EWindow* w : EWindow::window_list)
	{
		w->default_resize_event();
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	std::cout << "scroll: " << std::to_string(yoffset) << std::endl;
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



