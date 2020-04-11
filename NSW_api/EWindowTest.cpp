#pragma once
#include "EWindowTest.h"
#include "EntityManager.h"
#include "EPath.h"


std::string s;

int maximum_alloy = 0;

EWindowTest::EWindowTest()
{
	for (int i=0; i<ECluster::CLUSTER_DIM; i++)
	for (int j=0; j<ECluster::CLUSTER_DIM; j++)
	{
		ECluster::clusters[j][i] = new ECluster();
	}

	//std::cout << "Ceil(0.001) = " << ceil(0.001f) << std::endl;
	for (int i = 0; i < 100; i++)
	{
		Entity* en = new Entity();

		//Entity::entity_list.push_back(en);
		*en->position_x = (float) (rand() % 500) + 50.0f;
		*en->position_y = (float) (rand() % 500) + 50.0f;

		ECluster::put_entity(en, *en->position_x, *en->position_y);
	}

	always_fullscreen = true;

	for (int j = 0; j < EPath::PATH_SIZE; j++)
	for (int i = 0; i < EPath::PATH_SIZE; i++)
	{
		if (rand() % 10 == 0)
		{ EPath::block[j][i] = 100; }
		else
		{ EPath::block[j][i] = 5; }

		EPath::path[j][i][0] = 100;
		EPath::path[j][i][1] = 100;
	}

}
	



EWindowTest::~EWindowTest()
{
}

void EWindowTest::default_update(float _d)
{
}

void EWindowTest::update(float _d)
{
	if (glfwGetKey(EWindow::main_window, GLFW_KEY_A) == GLFW_PRESS)
	{game_camera->position_x -= _d * 300.0f; }

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_D) == GLFW_PRESS)
	{game_camera->position_x += _d * 300.0f; }

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_S) == GLFW_PRESS)
	{game_camera->position_y -= _d * 300.0f; }

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_W) == GLFW_PRESS)
	{game_camera->position_y += _d * 300.0f; }


	int draw_border_left =	(int)((game_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f) / ECluster::CLUSTER_SIZE) - 0; if (draw_border_left < 0) { draw_border_left = 0; }
	int draw_border_right = (int)((game_camera->position_x + EGraphicCore::SCR_WIDTH / 2.0f) / ECluster::CLUSTER_SIZE) + 0; if (draw_border_right >= ECluster::CLUSTER_DIM) { draw_border_right = ECluster::CLUSTER_DIM - 1;; }

	int draw_border_down =	(int)((game_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f) / ECluster::CLUSTER_SIZE) - 0; if (draw_border_down < 0) { draw_border_down = 0; }
	int draw_border_up =	(int)((game_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f) / ECluster::CLUSTER_SIZE) + 0; if (draw_border_up > ECluster::CLUSTER_DIM) { draw_border_up = ECluster::CLUSTER_DIM - 1; }

	
	for (int i = draw_border_up;	i >= draw_border_down;	i--)
	for (int j = draw_border_left;	j <= draw_border_right;	j++)
	for (Entity* e : ECluster::clusters[j][i]->entity_list)
	{
		int path_pos_x = (int)(*e->position_x / EPath::PATH_SIZE);
		int path_pos_y = (int)(*e->position_y / EPath::PATH_SIZE);

		if (EPath::path[path_pos_x - 1][path_pos_y][EPath::active_buffer] < EPath::path[path_pos_x][path_pos_y][EPath::active_buffer]) { *e->position_x -= _d * 50.0f; }
		if (EPath::path[path_pos_x + 1][path_pos_y][EPath::active_buffer] < EPath::path[path_pos_x][path_pos_y][EPath::active_buffer]) { *e->position_x += _d * 50.0f; }
		
		if (EPath::path[path_pos_x][path_pos_y - 1][EPath::active_buffer] < EPath::path[path_pos_x][path_pos_y][EPath::active_buffer]) { *e->position_y -= _d * 50.0f; }
		if (EPath::path[path_pos_x][path_pos_y + 1][EPath::active_buffer] < EPath::path[path_pos_x][path_pos_y][EPath::active_buffer]) { *e->position_y += _d * 50.0f; }
	}

}

void EWindowTest::default_draw(float _d)
{
}

void EWindowTest::draw(float _d)
{
	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3((EGraphicCore::SCR_WIDTH / 2.0f - game_camera->position_x) * EGraphicCore::correction_x - 1, (EGraphicCore::SCR_HEIGHT / 2.0f - game_camera->position_y) * EGraphicCore::correction_y - 1, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x, EGraphicCore::correction_y, 1));

	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	//----------------PATH MATRIX GABARITES----------------
	int left_path_draw = (int)((game_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f) / EPath::PATH_SIZE); if (left_path_draw < 0) { left_path_draw = 0; }
	int right_path_draw = (int)((game_camera->position_x + EGraphicCore::SCR_WIDTH / 2.0f) / EPath::PATH_SIZE); if (right_path_draw >= EPath::PATH_DIM) { right_path_draw = EPath::PATH_DIM - 1; }

	int down_path_draw = (int)((game_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f) / EPath::PATH_SIZE); if (down_path_draw < 0) { down_path_draw = 0; }
	int up_path_draw = (int)((game_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f) / EPath::PATH_SIZE); if (up_path_draw >= EPath::PATH_DIM) { up_path_draw = EPath::PATH_DIM - 1; }
	

	

	//----------------PATH MATRIX SPREAD----------------

	EPath::path[(int)((game_camera->position_x + EGraphicCore::SCR_WIDTH / 200.0f) / EPath::PATH_SIZE)][(int)((game_camera->position_y + EGraphicCore::SCR_HEIGHT / 200.0f) / EPath::PATH_SIZE)][EPath::back_buffer] = 0;
	
	if (EPath::phase == Enums::HEATMAP_PHASE::PHASE_UP)
	{
		for (int j = left_path_draw; j <= right_path_draw; j++)
		for (int i = down_path_draw; i < up_path_draw; i++)
		{
			if (EPath::path[j][i + 1][EPath::back_buffer] > EPath::path[j][i][EPath::back_buffer])
			{
				EPath::path[j][i + 1][EPath::back_buffer] = EPath::path[j][i][EPath::back_buffer] + EPath::block[j][i + 1];
			}
		}
	}

	if (EPath::phase == Enums::HEATMAP_PHASE::PHASE_DOWN)
	{
		for (int j = left_path_draw; j <= right_path_draw; j++)
		for (int i = up_path_draw; i > down_path_draw; i--)
		{
			if (EPath::path[j][i - 1][EPath::back_buffer] > EPath::path[j][i][EPath::back_buffer])
			{
				EPath::path[j][i - 1][EPath::back_buffer] = EPath::path[j][i][EPath::back_buffer] + EPath::block[j][i - 1];
			}
		}
	}

	if (EPath::phase == Enums::HEATMAP_PHASE::PHASE_RIGHT)
	{
		for (int i = down_path_draw; i <= up_path_draw; i++)
		for (int j = left_path_draw; j < right_path_draw; j++)
		
		{
			if (EPath::path[j + 1][i][EPath::back_buffer] > EPath::path[j][i][EPath::back_buffer])
			{
				EPath::path[j + 1][i][EPath::back_buffer] = EPath::path[j][i][EPath::back_buffer] + EPath::block[j + 1][i];
			}
		}
	}

	if (EPath::phase == Enums::HEATMAP_PHASE::PHASE_LEFT)
	{
		for (int i = down_path_draw; i <= up_path_draw; i++)
		for (int j = right_path_draw; j > left_path_draw; j--)
		
		{
			if (EPath::path[j - 1][i][EPath::back_buffer] > EPath::path[j][i][EPath::back_buffer])
			{
				EPath::path[j - 1][i][EPath::back_buffer] = EPath::path[j][i][EPath::back_buffer] + EPath::block[j - 1][i];
			}
		}
	}

	EPath::phase++;
	if (EPath::phase == Enums::HEATMAP_PHASE::PHASE_HEATING)
	{
		EPath::phase = 0;

		for (int j = left_path_draw; j <= right_path_draw; j++)
		for (int i = down_path_draw; i <= up_path_draw; i++)
		{
			EPath::path[j][i][EPath::back_buffer] += 4;
		}

		int swap_buffer = EPath::back_buffer;
		EPath::back_buffer = EPath::active_buffer;
		EPath::active_buffer = swap_buffer;
	}

	for (int j = 0; j < EPath::PATH_DIM; j++)
	{
		if (EPath::path[j][EPath::clamp_phase][EPath::back_buffer] > 1000) { EPath::path[j][EPath::clamp_phase][EPath::back_buffer] = 1000; }
		if (EPath::path[j][EPath::clamp_phase][EPath::active_buffer] > 1000) { EPath::path[j][EPath::clamp_phase][EPath::active_buffer] = 1000; }
	}

	EPath::clamp_phase++;
	if (EPath::clamp_phase >= EPath::PATH_DIM)
	{
		EPath::clamp_phase = 0;
	}
	//for (int i = EPath::clamp_phase; i < EPath::PATH_DIM; i++)



	//----------------DRAW PATH MATRIX----------------
	for (int i = up_path_draw; i >= down_path_draw; i--)
	for (int j = left_path_draw; j <= right_path_draw; j++)
	{
		if (EPath::block[j][i] >= 100)
		{
			EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		}
		else
		{
			EGraphicCore::batch->setcolor_lum(EColor::COLOR_WHITE, 1.0f - EMath::clamp_value_float(EPath::path[j][i][EPath::active_buffer] / 100.0f, 0.0f, 1.0f));
		}

		EGraphicCore::batch->draw_gabarite(j * EPath::PATH_SIZE, i * EPath::PATH_SIZE, EPath::PATH_SIZE, EPath::PATH_SIZE, EGraphicCore::gabarite_white_pixel);
	}

	//----------------DRAW ENTITIES----------------
	int draw_border_left =	(int)((game_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f) / ECluster::CLUSTER_SIZE) - 0; if (draw_border_left < 0) { draw_border_left = 0; }
	int draw_border_right = (int)((game_camera->position_x + EGraphicCore::SCR_WIDTH / 2.0f) / ECluster::CLUSTER_SIZE) + 0; if (draw_border_right >= ECluster::CLUSTER_DIM) { draw_border_right = ECluster::CLUSTER_DIM - 1;; }

	int draw_border_down =	(int)((game_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f) / ECluster::CLUSTER_SIZE) - 0; if (draw_border_down < 0) { draw_border_down = 0; }
	int draw_border_up =	(int)((game_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f) / ECluster::CLUSTER_SIZE) + 0; if (draw_border_up > ECluster::CLUSTER_DIM) { draw_border_up = ECluster::CLUSTER_DIM - 1; }

	
	for (int i = draw_border_up;	i >= draw_border_down;	i--)
	for (int j = draw_border_left;	j <= draw_border_right;	j++)
	{
		EGraphicCore::batch->setcolor(EColor::COLOR_BLACK);
		EGraphicCore::batch->draw_rama(j * ECluster::CLUSTER_SIZE, i * ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, 2, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		for (Entity* e : ECluster::clusters[j][i]->entity_list)
		{
			EGraphicCore::batch->draw_gabarite(*e->position_x - 10.0f, *e->position_y - 10.0f, 20.0f, 20.0f, EGraphicCore::gabarite_white_pixel);
		}
	}

	
	/*EGraphicCore::batch->setcolor(EColor::COLOR_BLACK);
	EGraphicCore::batch->draw_gabarite(100.0f + rand() % 10, 200.0f, 512.0f, 64.0f, EGraphicCore::gabarite_white_pixel);*/
}

void EWindowTest::draw_interface(float _d)
{
}
