#pragma once
#include "EWindowTest.h"

#include "EWindowEditor.h"
#include "EBA.h"


std::string s;

int maximum_alloy = 0;

void EWindowTest::test_of_values()
{
	float test_result = 0.0f;


	add_time_process(" # test begin # ");
	for (int i = 0; i < 1000000; i++)
	{
		test_result = test_value_A * test_value_B + i;
	}
	stop = std::chrono::high_resolution_clock::now();
	std::cout << "non vector" << (std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000.0f) << std::endl;
	start = std::chrono::high_resolution_clock::now();

	/////
	test_result = 0.0f;

	for (int i = 0; i < 1000000; i++)
	{
		test_result = test_vector.at(0) * test_vector.at(1) + i;
	}
	stop = std::chrono::high_resolution_clock::now();
	std::cout << "vector" << (std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000.0f) << std::endl;
	start = std::chrono::high_resolution_clock::now();

	///////

	test_result = 0.0f;

	//add_time_process("time of non-vector");

	float* addr_A = &test_vector.at(0);
	float* addr_B = &test_vector.at(0);

	std::cout << "addr" << addr_A << std::endl;
	std::cout << "addr value" << *addr_A << std::endl;

	for (int i = 0; i < 1000000; i++)
	{
		test_result = *addr_A * *addr_B + i;
	}
	stop = std::chrono::high_resolution_clock::now();
	std::cout << "vector with pointer" << (std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000.0f) << std::endl;
	start = std::chrono::high_resolution_clock::now();
	//add_time_process("time of vector");
}

EWindowTest::EWindowTest():EWindow()
{
	//test_of_values();

	for (int i = 1; i <= 5; i++)
	{
		terrain_textures_list.push_back
		(ETextureAtlas::put_texture_to_atlas("data/textures/terrain_c18_pavement_" + std::to_string(i) + ".png", EWindow::default_texture_atlas));
	}

	generate_terrain();

	Entity::HIT_ACTIONS_LIST.push_back(Entity::test_hit_action_destroy_touch);
	Entity::HIT_ACTION_NAME_LIST.push_back("test_hit");

	for (int i=0; i<ECluster::CLUSTER_DIM; i++)
	for (int j=0; j<ECluster::CLUSTER_DIM; j++)
	{
		ECluster::clusters[j][i] = new ECluster();
	}

	//std::cout << "Ceil(0.001) = " << ceil(0.001f) << std::endl;
	for (int i = 0; i < 00; i++)
	{
		Entity* en = new Entity();

		//Entity::entity_list.push_back(en);
		*en->position_x = (float) (rand() % 1000) + ECluster::CLUSTER_SIZE * ECluster::CLUSTER_DIM /2.0f;
		*en->position_y = (float)(rand() % 1000) + ECluster::CLUSTER_SIZE * ECluster::CLUSTER_DIM / 2.0f;

		ECluster::put_entity(en, *en->position_x, *en->position_y);
	}

	
	always_fullscreen = true;
	short default_path = 250;

	/*
	for (int j = 0; j < EPath::PATH_DIM; j++)
	for (int i = 0; i < EPath::PATH_DIM; i++)
	{
		if (rand() % 100 == 0)
		{ EPath::block[j][i] = true; }
		else
		{ EPath::block[j][i] = false; }

		EPath::path[j][i][0] = default_path;
		EPath::path[j][i][1] = default_path;
	}
	*/

	

}
	



EWindowTest::~EWindowTest()
{
}

void EWindowTest::default_update(float _d)
{
}

void EWindowTest::update(float _d)
{

	add_time_process("UPDATE BEGIN");

	//glfwGetCursorPos(EWindow::main_window, &EWindow::mouse_x, &EWindow::mouse_y);




	//crosshair_pos_x = EMath::clamp_value_float(crosshair_pos_x, 0.0f, EGraphicCore::SCR_WIDTH - 1.0f);
	//crosshair_pos_y = EMath::clamp_value_float(crosshair_pos_y, 0.0f, EGraphicCore::SCR_HEIGHT - 1.0f);
	if
	(
		(glfwGetWindowAttrib(EWindow::main_window, GLFW_FOCUSED) == 1)
		&
		(!EWindow::window_editor->is_active)
	)
	{
		SetCursorPos(1920.0 / 2.0f, 1080.0 / 2.0f);
		prev_mouse_x = 1920.0 / 2.0f;
		prev_mouse_y = 1080.0 / 2.0f;
	}


	if (EWindow::scroll > 0) game_camera->zoom /= 0.5f;
	if (EWindow::scroll < 0) game_camera->zoom *= 0.5f;

	if (EWindow::window_editor->is_active)
	{
		if (glfwGetKey(EWindow::main_window, GLFW_KEY_W) == GLFW_PRESS) { free_camera_y += 512.0f / game_camera->zoom * _d; }
		if (glfwGetKey(EWindow::main_window, GLFW_KEY_S) == GLFW_PRESS) { free_camera_y -= 512.0f / game_camera->zoom * _d; }
																								 
		if (glfwGetKey(EWindow::main_window, GLFW_KEY_A) == GLFW_PRESS) { free_camera_x -= 512.0f / game_camera->zoom * _d; }
		if (glfwGetKey(EWindow::main_window, GLFW_KEY_D) == GLFW_PRESS) { free_camera_x += 512.0f / game_camera->zoom * _d; }
	}

	if (EWindow::window_editor->is_active)
	{
		_d = 0.0f;
	}

	if (link_to_player != NULL)
		if (!glfwGetKey(EWindow::main_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			if ((!EWindow::window_editor->is_active))
			{
				if (EWindow::RMB)
				{
					game_camera->position_x = *link_to_player->position_x * game_camera->zoom + (EWindow::mouse_x - EGraphicCore::SCR_WIDTH / 2.0f) * 0.5f;
					game_camera->position_y = *link_to_player->position_y * game_camera->zoom + (EWindow::mouse_y - EGraphicCore::SCR_HEIGHT / 2.0f) * 0.5f;
				}
				else
				{
					game_camera->position_x = *link_to_player->position_x * game_camera->zoom + (EWindow::mouse_x - EGraphicCore::SCR_WIDTH / 2.0f) * 0.00f;
					game_camera->position_y = *link_to_player->position_y * game_camera->zoom + (EWindow::mouse_y - EGraphicCore::SCR_HEIGHT / 2.0f) * 0.00f;
				}

			}

		}

	if (EWindow::window_editor->is_active)
	{
		game_camera->position_x = free_camera_x * game_camera->zoom;
		game_camera->position_y = free_camera_y * game_camera->zoom;
	}

	game_camera->position_x = round(game_camera->position_x);
	game_camera->position_y = round(game_camera->position_y);



	

	//crosshair_pos_x = ECamera::get_world_position_x(game_camera);
	//crosshair_pos_y = ECamera::get_world_position_y(game_camera);
	crosshair_add_x += EWindow::mouse_speed_x / 1.0f;
	crosshair_add_y += EWindow::mouse_speed_y / 1.0f;
	
	crosshair_add_x = EMath::clamp_value_float(crosshair_add_x, -0.0f, EGraphicCore::SCR_WIDTH / 1.0f);
	crosshair_add_y = EMath::clamp_value_float(crosshair_add_y, -0.0f, EGraphicCore::SCR_HEIGHT / 1.0f);


	crosshair_pos_x = (game_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f + crosshair_add_x) / game_camera->zoom;
	crosshair_pos_y = (game_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f + crosshair_add_y) / game_camera->zoom ;

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_F1) == GLFW_PRESS) & (!EWindow::button_main_group_pressed))
	{
		EWindow::window_editor->is_active = !EWindow::window_editor->is_active;

		EWindow::button_main_group_pressed = true;

		if (EWindow::window_editor->is_active)
		{glfwSetInputMode(EWindow::main_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);}
		else
		{glfwSetInputMode(EWindow::main_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); }
	}

	if (false)
	{
		if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
		{
			if (LMB)
			{
				EPath::block
					[EMath::clamp_value_int((int)(ECamera::get_world_position_x(game_camera) / EPath::PATH_SIZE), 0, EPath::PATH_DIM - 1)]
				[EMath::clamp_value_int((int)(ECamera::get_world_position_y(game_camera) / EPath::PATH_SIZE), 0, EPath::PATH_DIM - 1)]
				= true;



				//EPath::block[0][0] = 1000;
			}

			if (RMB)
			{
				EPath::block
					[EMath::clamp_value_int((int)(ECamera::get_world_position_x(game_camera) / EPath::PATH_SIZE), 0, EPath::PATH_DIM - 1)]
				[EMath::clamp_value_int((int)(ECamera::get_world_position_y(game_camera) / EPath::PATH_SIZE), 0, EPath::PATH_DIM - 1)]
				= false;

				//EPath::block[0][0] = 1000;
			}
		}
	}

	

	//----------------PATH MATRIX GABARITES----------------
	left_path_draw = (int)((game_camera->position_x / game_camera->zoom - EGraphicCore::SCR_WIDTH / 2.0f / game_camera->zoom) / EPath::PATH_SIZE) - 10; if (left_path_draw < 0) { left_path_draw = 0; }
	right_path_draw = (int)((game_camera->position_x / game_camera->zoom + EGraphicCore::SCR_WIDTH / 2.0f / game_camera->zoom) / EPath::PATH_SIZE) + 10; if (right_path_draw >= EPath::PATH_DIM) { right_path_draw = EPath::PATH_DIM - 1; }

	down_path_draw = (int)((game_camera->position_y / game_camera->zoom - EGraphicCore::SCR_HEIGHT / 2.0f / game_camera->zoom) / EPath::PATH_SIZE) - 10; if (down_path_draw < 0) { down_path_draw = 0; }
	up_path_draw = (int)((game_camera->position_y / game_camera->zoom + EGraphicCore::SCR_HEIGHT / 2.0f / game_camera->zoom) / EPath::PATH_SIZE) + 10; if (up_path_draw >= EPath::PATH_DIM) { up_path_draw = EPath::PATH_DIM - 1; }

	//----------------DRAW BORDER GABARITES----------------
	draw_border_left = (int)((game_camera->position_x - EGraphicCore::SCR_WIDTH / 1.0f) / game_camera->zoom / ECluster::CLUSTER_SIZE) - 1; if (draw_border_left < 0) { draw_border_left = 0; }
	draw_border_right = (int)((game_camera->position_x + EGraphicCore::SCR_WIDTH / 1.0f) / game_camera->zoom / ECluster::CLUSTER_SIZE) + 1; if (draw_border_right >= ECluster::CLUSTER_DIM) { draw_border_right = ECluster::CLUSTER_DIM - 1;; }

	draw_border_down = (int)((game_camera->position_y - EGraphicCore::SCR_HEIGHT / 1.0f) / game_camera->zoom / ECluster::CLUSTER_SIZE) - 1; if (draw_border_down < 0) { draw_border_down = 0; }
	draw_border_up = (int)((game_camera->position_y + EGraphicCore::SCR_HEIGHT / 1.0f) / game_camera->zoom / ECluster::CLUSTER_SIZE) + 1; if (draw_border_up >= ECluster::CLUSTER_DIM) { draw_border_up = ECluster::CLUSTER_DIM - 1; }

	//----------------UPDATE BORDER GABARITES----------------
	update_border_left = (int)((game_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f) / game_camera->zoom / ECluster::CLUSTER_SIZE) - 3; if (update_border_left < 0) { update_border_left = 0; }
	update_border_right = (int)((game_camera->position_x + EGraphicCore::SCR_WIDTH / 2.0f) / game_camera->zoom / ECluster::CLUSTER_SIZE) + 3; if (update_border_right >= ECluster::CLUSTER_DIM) { update_border_right = ECluster::CLUSTER_DIM - 1;; }

	update_border_down = (int)((game_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f) / game_camera->zoom / ECluster::CLUSTER_SIZE) - 3; if (update_border_down < 0) { update_border_down = 0; }
	update_border_up = (int)((game_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f) / game_camera->zoom / ECluster::CLUSTER_SIZE) + 3; if (update_border_up >= ECluster::CLUSTER_DIM) { update_border_up = ECluster::CLUSTER_DIM - 1; }


		//remove/destroy entities
	for (int i = update_border_up; i >= update_border_down; i--)
	for (int j = update_border_left; j <= update_border_right; j++)
	{
		for (int k = 0; k < ECluster::clusters[j][i]->entity_list.size(); k++)
		{
			Entity* e = ECluster::clusters[j][i]->entity_list.at(k);

			if (*e->need_remove)
			{
				ECluster::clusters[j][i]->entity_list.erase(ECluster::clusters[j][i]->entity_list.begin() + k);
				k--;
			}

		
		}
	}
	//

	add_time_process("remove entities");

	int left_path_heat_draw = left_path_draw - 1;		if (left_path_heat_draw < 0)					{ left_path_heat_draw = 0; }
	int right_path_heat_draw = right_path_draw + 1;		if (right_path_heat_draw >= EPath::PATH_DIM)	{ right_path_heat_draw = EPath::PATH_DIM - 1; }

	int up_path_heat_draw = up_path_draw + 1;			if (up_path_heat_draw >= EPath::PATH_DIM)		{ up_path_heat_draw = EPath::PATH_DIM - 1; }
	int down_path_heat_draw = down_path_draw - 1;		if (down_path_heat_draw < 0)					{ down_path_heat_draw = 0; }
	//----------------ENTITIES PATH FIND----------------
	for (int i = update_border_up;		i >= update_border_down;	i--)
	for (int j = update_border_left;	j <= update_border_right;	j++)
	for (Entity* e : ECluster::clusters[j][i]->entity_list)
	if ((!*e->inmovable) & (!*e->is_bullet))
	{
		//clear block
		EPath::entity_block[(int)(*e->position_x / EPath::PATH_SIZE)][(int)(*e->position_y / EPath::PATH_SIZE)] = true;
	}

	add_time_process("add entity block");


	//if (!EPath::block[(int)((game_camera->position_x + EGraphicCore::SCR_WIDTH / 200.0f) / EPath::PATH_SIZE)][(int)((game_camera->position_y + EGraphicCore::SCR_HEIGHT / 200.0f) / EPath::PATH_SIZE)])
	//{
	//	EPath::path[(int)((game_camera->position_x + EGraphicCore::SCR_WIDTH / 200.0f) / EPath::PATH_SIZE)][(int)((game_camera->position_y + EGraphicCore::SCR_HEIGHT / 200.0f) / EPath::PATH_SIZE)][EPath::back_buffer] = 0;
	//}

	EPath::cooldown -= _d;

	if (EWindow::window_editor->is_active) { EPath::cooldown = 0.0f; }

	if (EPath::cooldown <= 0)
	{
		EPath::cooldown += 0.02f;

		if (EPath::phase == Enums::HEATMAP_PHASE::PHASE_UP)
		{
			for (int j = left_path_draw; j <= right_path_draw; j++)
				for (int i = down_path_draw; i < up_path_draw; i++)
				{
					if ((!EPath::block[j][i + 1]) && (!EPath::entity_block[j][i + 1]) && (EPath::path[j][i + 1][EPath::back_buffer] > EPath::path[j][i][EPath::back_buffer]))
					{
						EPath::path[j][i + 1][EPath::back_buffer] = EPath::path[j][i][EPath::back_buffer] + 4;
					}
				}
		}

		if (EPath::phase == Enums::HEATMAP_PHASE::PHASE_DOWN)
		{
			for (int j = left_path_draw; j <= right_path_draw; j++)
				for (int i = up_path_draw; i > down_path_draw; i--)
				{
					if ((!EPath::block[j][i - 1]) && (!EPath::entity_block[j][i - 1]) && (EPath::path[j][i - 1][EPath::back_buffer] > EPath::path[j][i][EPath::back_buffer]))
					{
						EPath::path[j][i - 1][EPath::back_buffer] = EPath::path[j][i][EPath::back_buffer] + 4;
					}
				}
		}

		if (EPath::phase == Enums::HEATMAP_PHASE::PHASE_RIGHT)
		{
			for (int i = down_path_draw; i <= up_path_draw; i++)
				for (int j = left_path_draw; j < right_path_draw; j++)

				{
					if ((!EPath::block[j + 1][i]) && (!EPath::entity_block[j + 1][i]) && (EPath::path[j + 1][i][EPath::back_buffer] > EPath::path[j][i][EPath::back_buffer]))
					{
						EPath::path[j + 1][i][EPath::back_buffer] = EPath::path[j][i][EPath::back_buffer] + 4;
					}
				}
		}

		if (EPath::phase == Enums::HEATMAP_PHASE::PHASE_LEFT)
		{
			for (int i = down_path_draw; i <= up_path_draw; i++)
				for (int j = right_path_draw; j > left_path_draw; j--)

				{
					if ((!EPath::block[j - 1][i]) && (!EPath::entity_block[j - 1][i]) && (EPath::path[j - 1][i][EPath::back_buffer] > EPath::path[j][i][EPath::back_buffer]))
					{
						EPath::path[j - 1][i][EPath::back_buffer] = EPath::path[j][i][EPath::back_buffer] + 4;
					}
				}
		}

		EPath::phase++;
		if (EPath::phase == Enums::HEATMAP_PHASE::PHASE_HEATING)
		{
			EPath::phase = 0;

			for (int j = left_path_heat_draw; j <= right_path_heat_draw; j++)
				for (int i = down_path_heat_draw; i <= up_path_heat_draw; i++)
				{
					EPath::path[j][i][EPath::back_buffer] += 16;
				}

			int swap_buffer = EPath::back_buffer;
			EPath::back_buffer = EPath::active_buffer;
			EPath::active_buffer = swap_buffer;
		}
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

add_time_process("calculate path");

	for (int i = draw_border_up;	i >= draw_border_down;	i--)
	for (int j = draw_border_left;	j <= draw_border_right;	j++)
	for (Entity* e : ECluster::clusters[j][i]->entity_list)
	//if (!*e->already_updated)
	if ((!*e->inmovable) & (!*e->is_bullet))
	{
		//clear block
		EPath::entity_block[(int)(*e->position_x / EPath::PATH_SIZE)][(int)(*e->position_y / EPath::PATH_SIZE)] = false;
	}

	add_time_process("path entity unblock");

	int prev_cluster_x = 0;
	int prev_cluster_y = 0;

	if (!new_added_entity_list.empty())
	{
		for (Entity* e : new_added_entity_list)
		{
			ECluster::put_entity(e);
		}

		new_added_entity_list.clear();
	}

	add_time_process("put new entity");
	
	for (int i = update_border_up;		i >= update_border_down; i--)
	for (int j = update_border_left;	j <= update_border_right; j++)
	for (Entity* e : ECluster::clusters[j][i]->entity_list)
	{
		if (*e->have_lifetime)
		{
			*e->lifetime -= _d;

			if (*e->lifetime <= 0)
			{
				*e->need_remove = true;
			}
		}
		if (*e->shoot_cooldown > 0)
		{*e->shoot_cooldown -= _d;}

		int dir_x = 0;
		int dir_y = 0;
		float dir_mul = 1.0f;

		*e->already_moved_x = false;
		*e->already_moved_y = false;

		if (e->controlled_by_player)
		{
			if (glfwGetKey(EWindow::main_window, GLFW_KEY_A) == GLFW_PRESS) {dir_x = -1;}

			if (glfwGetKey(EWindow::main_window, GLFW_KEY_D) == GLFW_PRESS)	{dir_x = 1;}

			if (glfwGetKey(EWindow::main_window, GLFW_KEY_S) == GLFW_PRESS)	{dir_y = -1;}

			if (glfwGetKey(EWindow::main_window, GLFW_KEY_W) == GLFW_PRESS) {dir_y = 1;}

			float ray_length_x = crosshair_pos_x - *e->position_x;
			float ray_length_y = crosshair_pos_y - *e->position_y;

			float angleInRadian = atan2(ray_length_x, ray_length_y);
			float angleInDegree = angleInRadian * 180 / 3.1415926;



			*e->target_angle_id = angleInDegree + 22.5f;
			if (*e->target_angle_id < 0) { *e->target_angle_id += 360; }
			*e->target_angle_id = (int)((*e->target_angle_id) / 45.0f);

			for (int y = 0; y< 1; y++)
			if ((LMB) & (true) & (!EWindow::window_editor->is_active))
			{


				if (*e->shoot_cooldown <= 0.0f)
				{
					*e->shoot_cooldown += 0.100f;

					Entity* bullet = new Entity();
					*bullet->position_x = *e->position_x;
					*bullet->position_y = *e->position_y;

					*bullet->collision_down = 3.0f;
					*bullet->collision_left = 3.0f;
					*bullet->collision_right = 3.0f;
					*bullet->collision_up = 3.0f;

					*bullet->lifetime = 1.0f;
					*bullet->have_lifetime = true;

					*bullet->mass = 1.0;

					*bullet->is_bullet = true;

					bullet->action_on_hit = &Entity::test_hit_action_self_destroy_on_hit;

					
					//float ray_length_x = ECamera::get_world_position_x(game_camera) - *e->position_x;
					//float ray_length_y = ECamera::get_world_position_y(game_camera) - *e->position_y;
					




					/*std::cout << "angle is:" << angleInDegree << std::endl;

					std::cout << "ray x:" << ray_length_x << std::endl;
					std::cout << "ray y:" << ray_length_y << std::endl;*/
					//float new_angle = angleInDegree;
					//EFont::active_font->draw(EGraphicCore::batch, std::to_string(angleInDegree), ECamera::get_world_position_x(game_camera), ECamera::get_world_position_y(game_camera));

					float dst = sqrt(ray_length_x * ray_length_x + ray_length_y * ray_length_y) + 1.0f;
					//std::cout << "dst:" << dst << std::endl;

					float recoil_angle = (angleInDegree + 5.0f - rand() % 10) * 3.1415926f / 180.0f;

					float new_x = sin(recoil_angle) * dst;
					float new_y = cos(recoil_angle) * dst;

					//std::cout << "sin:" << new_x << std::endl;
					//std::cout << "cos:" << new_y << std::endl;

					crosshair_add_x = new_x + EGraphicCore::SCR_WIDTH / 2.0f;
					crosshair_add_y = new_y + EGraphicCore::SCR_HEIGHT / 2.0f;

					//SetCursorPos(EWindow::real_mouse_x + (ECamera::get_world_position_x(game_camera) - new_x), EWindow::real_mouse_y + (ECamera::get_world_position_y(game_camera) - new_y));

					float mul_x = ray_length_x / dst;
					float mul_y = ray_length_y / dst;

					*bullet->speed_x += 10000.0f * mul_x;
					*bullet->speed_y += 10000.0f * mul_y;



					*bullet->real_speed_x = *bullet->speed_x * _d;
					*bullet->real_speed_y = *bullet->speed_y * _d;

					ESprite* spr = new ESprite();

					bullet->sprite_list.push_back(spr);

					//ECluster::put_entity(bullet);

					new_added_entity_list.push_back(bullet);

				}
			}

			if (EPath::phase == Enums::HEATMAP_PHASE::PHASE_UP)
			if (!EPath::block[(int)(*e->position_x / EPath::PATH_SIZE)][(int)(*e->position_y  / EPath::PATH_SIZE)])
			{
				EPath::path[(int)(*e->position_x / EPath::PATH_SIZE)][(int)(*e->position_y / EPath::PATH_SIZE)][EPath::active_buffer] = 1;
			}
		}

		if (e->controlled_by_ai)
		{
			int path_pos_left = (int)((*e->position_x - *e->collision_left - 2.0f) / EPath::PATH_SIZE);
			int path_pos_right = (int)((*e->position_x + *e->collision_right + 2.0f) / EPath::PATH_SIZE);

			int path_pos_up = (int)((*e->position_y + *e->collision_up + 2.0f) / EPath::PATH_SIZE);
			int path_pos_down = (int)((*e->position_y - *e->collision_down - 2.0f) / EPath::PATH_SIZE);

			int path_pos_x = (int)(*e->position_x / EPath::PATH_SIZE);
			int path_pos_y = (int)(*e->position_y / EPath::PATH_SIZE);






			short left_dir = EPath::path[path_pos_x - 1][path_pos_y][EPath::active_buffer];
			short right_dir = EPath::path[path_pos_x + 1][path_pos_y][EPath::active_buffer];

			short up_dir = EPath::path[path_pos_x][path_pos_y + 1][EPath::active_buffer];
			short down_dir = EPath::path[path_pos_x][path_pos_y - 1][EPath::active_buffer];

			short corner_A = EPath::path[path_pos_x - 1][path_pos_y + 1][EPath::active_buffer];
			short corner_B = EPath::path[path_pos_x + 1][path_pos_y + 1][EPath::active_buffer];

			short corner_C = EPath::path[path_pos_x + 1][path_pos_y - 1][EPath::active_buffer];
			short corner_D = EPath::path[path_pos_x - 1][path_pos_y - 1][EPath::active_buffer];

			//#*
			//**
			bool corner_block_A = EPath::block[path_pos_left][path_pos_up];

			//*#
			//**
			bool corner_block_B = EPath::block[path_pos_right][path_pos_up];

			//**
			//*#
			bool corner_block_C = EPath::block[path_pos_right][path_pos_down];

			//**
			//#*
			bool corner_block_D = EPath::block[path_pos_left][path_pos_down];

			bool block_current = EPath::block[path_pos_x][path_pos_y];

			//bool up_block = EPath::block[path_pos_left][path_pos_up] || EPath::block[path_pos_right][path_pos_up];
			//bool down_block = EPath::block[path_pos_left][path_pos_down] || EPath::block[path_pos_right][path_pos_down];


			//bool up_down_block = ((up_dir >= 1000) || (down_dir >= 1000));
			//bool left_right_block = ((left_dir >= 1000) || (right_dir >= 1000));

			short cur_dir = EPath::path[path_pos_x][path_pos_y][EPath::active_buffer];

			//EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
			//EGraphicCore::batch->draw_gabarite((path_pos_x - 1)* EPath::PATH_SIZE, path_pos_up* EPath::PATH_SIZE, EPath::PATH_SIZE, 10.0f, EGraphicCore::gabarite_white_pixel);

			short min_dir = cur_dir;
			//if ((cur_dir > 20))
			{
				//left
				if ((left_dir < min_dir))
				{
					min_dir = left_dir;
					dir_x = -1;
					dir_y = 0;
				}

				//right
				if (right_dir < min_dir)
				{
					min_dir = right_dir;
					dir_x = 1;
					dir_y = 0;
				}

				//down
				if (down_dir < min_dir)
				{
					min_dir = down_dir;
					dir_x = 0;
					dir_y = -1;
				}

				//up
				if (up_dir < min_dir)
				{
					min_dir = up_dir;
					dir_x = 0;
					dir_y = 1;
				}

				//up-left
				if (!block_current)
				{
					if ((corner_A < min_dir) && (left_dir < 500) && (up_dir < 500))
					{
						min_dir = corner_A;
						dir_x = -1;
						dir_y = 1;
					}

					//up-right
					if ((corner_B < min_dir) && (right_dir < 500) && (up_dir < 500))
					{
						min_dir = corner_B;
						dir_x = 1;
						dir_y = 1;
					}

					//down-right
					if ((corner_C < min_dir) && (right_dir < 500) && (down_dir < 500))
					{
						min_dir = corner_C;
						dir_x = 1;
						dir_y = -1;
					}

					//down-left
					if ((corner_D < min_dir) && (left_dir < 500) && (down_dir < 500))
					{
						min_dir = corner_D;
						dir_x = -1;
						dir_y = -1;
					}
				}
			}



			if (!block_current)
			{
				if (corner_block_A)
				{
					if (dir_x == -1) { dir_x = 0; dir_y = -1; }
					if (dir_y == 1) { dir_x = 1; dir_y = 0; }
				}

				if (corner_block_B)
				{
					if (dir_x == 1) { dir_x = 0; dir_y = -1; }
					if (dir_y == 1) { dir_x = -1; dir_y = 0; }
				}

				if (corner_block_C)
				{
					if (dir_x == 1) { dir_x = 0; dir_y = 1; }
					if (dir_y == -1) { dir_x = -1; dir_y = 0; }
				}

				if (corner_block_D)
				{
					if (dir_x == -1) { dir_x = 0; dir_y = 1; }
					if (dir_y == -1) { dir_x = 1; dir_y = 0; }
				}
			}

			if (dir_x * dir_y != 0)
			{
				dir_mul = 0.7f;
			}
		}

		//add_time_process("entities_path_find");

		*e->speed_x += dir_x * _d * 1000.0f * dir_mul;
		*e->speed_y += dir_y * _d * 1000.0f * dir_mul;

		*e->real_speed_x = *e->speed_x * _d;
		*e->real_speed_y = *e->speed_y * _d;


	}


		////
		////===>
		////

	add_time_process("entity control");

		float total_impulse = 0;
		float total_mass = 0;
		float transfer_multiplier = 0;
		float speed_diff = 0;

		float delta = 0;

		bool need_second_move_update = true;

		

		for (int u = 0; u < 2; u++)
		if ((u == 0)||(need_second_move_update))
		{

			for (int i = update_border_up;		i >= update_border_down; i--)
			for (int j = update_border_left;	j <= update_border_right; j++)
			for (Entity* e : ECluster::clusters[j][i]->entity_list)
			//if (!*e->already_updated)
				if (!*e->inmovable)
				{
					*e->real_speed_x = *e->speed_x * _d;
					*e->real_speed_y = *e->speed_y * _d;

					bool collision_left = *e->already_moved_x;
					bool collision_right = *e->already_moved_x;
					bool collision_up = *e->already_moved_y;
					bool collision_down = *e->already_moved_y;



					*e->already_updated = true;

					prev_cluster_x = (int)(*e->position_x / ECluster::CLUSTER_SIZE);
					prev_cluster_y = (int)(*e->position_y / ECluster::CLUSTER_SIZE);

					Entity* nearest_entity_left_side = NULL;
					Entity* nearest_entity_right_side = NULL;
					Entity* nearest_entity_up_side = NULL;
					Entity* nearest_entity_down_side = NULL;

					float nearest_dist_left_side = 99999.0f;
					float nearest_dist_right_side = 99999.0f;
					float nearest_dist_up_side = 99999.0f;
					float nearest_dist_down_side = 99999.0f;


					////////////////////////////////////////////////////////////////////////////////////////////////////////

					if ((EWindow::window_editor->is_active))
					{
						*link_to_player->real_speed_x = ECamera::get_world_position_x(game_camera) - *link_to_player->position_x;
						*link_to_player->real_speed_y = ECamera::get_world_position_y(game_camera) - *link_to_player->position_y;
					}

					int start_cluster_x = int(*e->position_x / ECluster::CLUSTER_SIZE);
					int start_cluster_y = int(*e->position_y / ECluster::CLUSTER_SIZE);
					if (*e->real_speed_x > 0) { start_cluster_x -= 3; } else { start_cluster_x += 3; }
					if (*e->real_speed_y > 0) { start_cluster_y -= 3; } else { start_cluster_y += 3; }
					//if (*e->real_speed_y > 0) { start_cluster_y -= 3; } else { start_cluster_y += 3; }

					int end_cluster_x = int((*e->position_x + *e->real_speed_x) / ECluster::CLUSTER_SIZE);
					int end_cluster_y = int((*e->position_y + *e->real_speed_y) / ECluster::CLUSTER_SIZE);
					if (*e->real_speed_x > 0) { end_cluster_x += 3; } else { end_cluster_x -= 3; }
					if (*e->real_speed_y > 0) { end_cluster_y += 3; } else { end_cluster_y -= 3; }


					int cluster_length_x = end_cluster_x - start_cluster_x;
					int cluster_length_y = end_cluster_y - start_cluster_y;

					int direction_x = 1;
					int direction_y = 1;

					if (cluster_length_x < 0) { direction_x = -1; }
					if (cluster_length_y < 0) { direction_y = -1; }

					int progress_x = 0;
					int progress_y = 0;


				for (int cx = start_cluster_x; cx != end_cluster_x + direction_x; cx += direction_x)
				{
					float projection_x = start_cluster_x;
					float projection_y = start_cluster_y;

					if (cluster_length_x != 0)
					{
						projection_x = cx;
						projection_y = start_cluster_y + cluster_length_y * progress_x / abs(cluster_length_x);
					}


					progress_y = 0;

						for (int cy = start_cluster_y; cy != end_cluster_y + direction_y; cy += direction_y)
						if
						(
							(cx >=0)&&(cy >=0)&&(cx < ECluster::CLUSTER_DIM) && (cy < ECluster::CLUSTER_DIM)
							&
							(abs(projection_y - cy) <= 3)
							||
							(
								(progress_x <=7) & (progress_y <= 7)
							)
							||
							(
								(progress_x >= abs(cluster_length_x) - 7) & (progress_y >= abs(cluster_length_y) - 7)
							)
						)
						{
							if ((e->controlled_by_player) & (EWindow::window_editor->is_active))
							{
								if (abs(projection_y - cy) <= 3)
								{EGraphicCore::batch->setcolor(EColor::COLOR_PINK);}
								else
								{EGraphicCore::batch->setcolor_lum(EColor::COLOR_PINK, 0.55f);}
								EGraphicCore::batch->draw_gabarite(cx * ECluster::CLUSTER_SIZE, cy * ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, EGraphicCore::gabarite_white_pixel);
								

								EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
								EGraphicCore::batch->draw_gabarite(projection_x * ECluster::CLUSTER_SIZE, projection_y * ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, EGraphicCore::gabarite_white_pixel);
							}

							if (!*e->already_moved_x)
							{

								//left_side
								if (*e->real_speed_x > 0)
								{
									for (Entity* e2 : ECluster::clusters[cx][cy]->entity_list)
										if ((e != e2) & (!(*e->is_bullet & *e2->is_bullet)))
										{
											if (ECluster::collision_left(e, e2))
											{
												if (*e2->position_x - *e2->collision_left - *e->position_x < nearest_dist_left_side)
												{
													nearest_dist_left_side = *e2->position_x - *e2->collision_left - *e->position_x;
													nearest_entity_left_side = e2;
													//EWindow::window_editor->selected_entity = nearest_entity_left_side;
												}
												collision_left = true;
											}
										}
								}

								//right_side
								if (*e->real_speed_x < 0)
								{
									for (Entity* e2 : ECluster::clusters[cx][cy]->entity_list)
										if ((e != e2) & (!(*e->is_bullet & *e2->is_bullet)))
										{
											if (ECluster::collision_right(e, e2))
											{
												if (*e->position_x - *e2->position_x - *e2->collision_right < nearest_dist_right_side)
												{
													nearest_dist_right_side = *e->position_x - *e2->position_x - *e2->collision_right;
													nearest_entity_right_side = e2;
												}

												collision_right = true;
											}
										}
								}
							}

							if (!*e->already_moved_y)
							{
								//up_side
								if (*e->real_speed_y < 0)
								{
									for (Entity* e2 : ECluster::clusters[cx][cy]->entity_list)
										if ((e != e2) & (!(*e->is_bullet & *e2->is_bullet)))
										{
											if (ECluster::collision_up(e, e2))
											{
												if (*e->position_y - *e2->position_y - *e2->collision_up < nearest_dist_up_side)
												{
													nearest_dist_up_side = *e->position_y - *e2->position_y - *e2->collision_up;
													nearest_entity_up_side = e2;
												}

												collision_up = true;
											}
										}
								}

								//down_side
								if (*e->real_speed_y > 0)
								{
									for (Entity* e2 : ECluster::clusters[cx][cy]->entity_list)
										if ((e != e2) & (!(*e->is_bullet & *e2->is_bullet)))
										{
											if (ECluster::collision_down(e, e2))
											{
												if (*e2->position_y - *e->position_y - *e2->collision_down < nearest_dist_down_side)
												{
													nearest_dist_down_side = *e->position_y - *e->position_y - *e2->collision_up;
													nearest_entity_down_side = e2;
												}
												collision_down = true;
											}
										}
								}
							}

							progress_y++;
						}
						else
						{
							progress_y++;
						}

						progress_x++;
				}

				if ((EWindow::window_editor->is_active))
				{
					*link_to_player->real_speed_x = 0.0f;
					*link_to_player->real_speed_y = 0.0f;
				}

				//end of collision detect
				if (nearest_entity_left_side != NULL)
				{*e->position_x = *nearest_entity_left_side->position_x - *nearest_entity_left_side->collision_left - *e->collision_right;}
				
				{

					//if (*e->real_speed_x * *e->real_speed_x < 0.05f) { *e->real_speed_x = 0.0f; }
					//if (*e->real_speed_y * *e->real_speed_y < 0.05f) { *e->real_speed_y = 0.0f; }

					if ((!collision_left) & (!collision_right) & (!*e->already_moved_x))
					{
						*e->position_x += *e->real_speed_x;
						*e->already_moved_x = true;

						*e->position_x = EMath::clamp_value_float(*e->position_x, 1.0f, ECluster::CLUSTER_SIZE * ECluster::CLUSTER_DIM);

					}

					if ((!collision_up) & (!collision_down) & (!*e->already_moved_y))
					{
						*e->position_y += *e->real_speed_y;
						*e->already_moved_y = true;

						*e->position_y = EMath::clamp_value_float(*e->position_y, 1.0f, ECluster::CLUSTER_SIZE * ECluster::CLUSTER_DIM);
					}
				}

				if (nearest_entity_left_side != NULL)
				{
					if (*e->real_speed_x > * nearest_entity_left_side->real_speed_x)
					{
						*e->speed_y *= pow(0.1, _d);

						if (*nearest_entity_left_side->inmovable) { *e->speed_x *= 0.5f; }
						else
						{
							total_mass = *e->mass + *nearest_entity_left_side->mass;
							total_impulse = (*e->mass * *e->speed_x) + (*nearest_entity_left_side->mass * *nearest_entity_left_side->speed_x);

							*e->speed_x = total_impulse / total_mass;
							*nearest_entity_left_side->speed_x = total_impulse / total_mass;
						}
					}

					

					if (e->action_on_hit != NULL) { e->action_on_hit(e, nearest_entity_left_side, Entity::Side::HIT_SIDE_LEFT); }
					if (e->action_on_hited != NULL) { e->action_on_hited(nearest_entity_left_side, e, Entity::Side::HIT_SIDE_LEFT); }
					//*e->position_x -= 1.0f;
				}

				if (nearest_entity_right_side != NULL)
				{
					if ((*e->speed_x) < (*nearest_entity_right_side->speed_x))
					{
						*e->speed_y *= pow(0.1, _d);

						if (*nearest_entity_right_side->inmovable) { *e->speed_x *= 0.5f; }
						else
						{
							total_mass = *e->mass + *nearest_entity_right_side->mass;
							total_impulse = (*e->mass * *e->speed_x) + (*nearest_entity_right_side->mass * *nearest_entity_right_side->speed_x);

							*e->speed_x = total_impulse / total_mass;
							*nearest_entity_right_side->speed_x = total_impulse / total_mass;
						}
						//*e->position_x -= 1.0f;
					}

					*e->position_x = *nearest_entity_right_side->position_x + *nearest_entity_right_side->collision_right + *e->collision_left;

					if (e->action_on_hit != NULL) { e->action_on_hit(e, nearest_entity_right_side, Entity::Side::HIT_SIDE_RIGHT); }
					if (e->action_on_hited != NULL) { e->action_on_hited(nearest_entity_right_side, e, Entity::Side::HIT_SIDE_RIGHT); }
				}

				if (nearest_entity_up_side != NULL)
				{
					if ((*e->speed_y) < (*nearest_entity_up_side->speed_y))
					{
						*e->speed_x *= pow(0.1, _d);

						if (*nearest_entity_up_side->inmovable) { *e->speed_y *= 0.5f; }
						else
						{
							total_mass = *e->mass + *nearest_entity_up_side->mass;
							total_impulse = (*e->mass * *e->speed_y) + (*nearest_entity_up_side->mass * *nearest_entity_up_side->speed_y);

							*e->speed_y = total_impulse / total_mass;
							*nearest_entity_up_side->speed_y = total_impulse / total_mass;
						}
						//*e->position_x -= 1.0f;
					}

					*e->position_y = *nearest_entity_up_side->position_y + *nearest_entity_up_side->collision_up + *e->collision_down;

					if (e->action_on_hit != NULL) { e->action_on_hit(e, nearest_entity_up_side, Entity::Side::HIT_SIDE_UP); }
					if (e->action_on_hited != NULL) { e->action_on_hited(nearest_entity_up_side, e, Entity::Side::HIT_SIDE_UP); }
				}

				if (nearest_entity_down_side != NULL)
				{
					if ((*e->speed_y) > (*nearest_entity_down_side->speed_y))
					{
						*e->speed_x *= pow(0.1, _d);

						if (*nearest_entity_down_side->inmovable) { *e->speed_y *= 0.5f; }
						else
						{
							total_mass = *e->mass + *nearest_entity_down_side->mass;
							total_impulse = (*e->mass * *e->speed_y) + (*nearest_entity_down_side->mass * *nearest_entity_down_side->speed_y);

							*e->speed_y = total_impulse / total_mass;
							*nearest_entity_down_side->speed_y = total_impulse / total_mass;
							//*e->position_x -= 1.0f;
						}
					}

					*e->position_y = *nearest_entity_down_side->position_y - *nearest_entity_down_side->collision_down - *e->collision_up;

					if (e->action_on_hit != NULL) { e->action_on_hit(e, nearest_entity_down_side, Entity::Side::HIT_SIDE_DOWN); }
					if (e->action_on_hited != NULL) { e->action_on_hited(nearest_entity_down_side, e, Entity::Side::HIT_SIDE_DOWN); }
				}


				//std::cout << "-------BONK!-------" << std::endl;
	



				if ((!*e->is_bullet) && (u == 0))
				{
					*e->speed_x *= pow(0.5, _d);
					*e->speed_y *= pow(0.5, _d);
				}


				int new_cluster_x = (int)(*e->position_x / ECluster::CLUSTER_SIZE);
				int new_cluster_y = (int)(*e->position_y / ECluster::CLUSTER_SIZE);

				if ((new_cluster_x != prev_cluster_x) || (new_cluster_y != prev_cluster_y))
				{*e->need_change_cluster = true;}

				//if (*e->is_bullet) { need_second_move_update = false; }
			}

			for (int i = draw_border_up; i >= draw_border_down; i--)
			for (int j = draw_border_left; j <= draw_border_right; j++)
			{
				for (int k = 0; k < ECluster::clusters[j][i]->entity_list.size(); k++)
				{
					Entity* e = ECluster::clusters[j][i]->entity_list.at(k);

					*e->already_updated = false;
					*e->updates_count = 0;

					if (*e->need_change_cluster)
					{
						ECluster::clusters[j][i]->entity_list.erase(ECluster::clusters[j][i]->entity_list.begin() + k);
						ECluster::put_entity(e, *e->position_x, *e->position_y);

						*e->need_change_cluster = false;

						k--;
					}
				}
			}


			//if (!any_collision) { u = 99999; break; }


		}

		add_time_process("entity collision and physic");


	//add_time_process("entities_update");

}

void EWindowTest::default_draw(float _d)
{
}

void EWindowTest::draw_shadows()
{

	//draw call terrain
	EGraphicCore::batch->force_draw_call();


	//active shadow FBO
	ETextureAtlas::active_this_texture_atlas(EWindow::shadow_FBO, EWindow::default_texture_atlas, game_camera->position_x, game_camera->position_y, game_camera->zoom);
	glClearColor(EColor::COLOR_SKY_AMBIENT->color_red, EColor::COLOR_SKY_AMBIENT->color_green, EColor::COLOR_SKY_AMBIENT->color_blue, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendEquation(GL_MAX);
	float scx = (EGraphicCore::SCR_WIDTH / EWindow::shadow_FBO->size_x);
	float scy = (EGraphicCore::SCR_HEIGHT / EWindow::shadow_FBO->size_y);

	float	cx = 1.0f / EGraphicCore::SCR_WIDTH * 2.0f * scx;
	float	cy = 1.0f / EGraphicCore::SCR_HEIGHT * 2.0f * scy;





	//set correct zoom
	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	//EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3((EGraphicCore::SCR_WIDTH / 2.0f - game_camera->position_x) * EGraphicCore::correction_x - 1, (EGraphicCore::SCR_HEIGHT / 2.0f - game_camera->position_y) * EGraphicCore::correction_y - 1, 0.0f));
	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3((EGraphicCore::SCR_WIDTH / 2.0f - game_camera->position_x) * cx - 1.0f, (EGraphicCore::SCR_HEIGHT / 2.0f - game_camera->position_y + 500.0f) * cy - 1.0f, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(cx * game_camera->zoom, cy * game_camera->zoom, 1));

	//use shader
	EGraphicCore::ourShader->use();

	unsigned int transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));
	EGraphicCore::batch->setcolor(EColor::COLOR_GRAY);

	//draw shadow texture
	for (int i = draw_border_up; i >= draw_border_down; i--)
	for (int j = draw_border_left; j <= draw_border_right; j++)
	for (Entity* e : ECluster::clusters[j][i]->entity_list)
	{
		Entity::draw_sprite(e, EGraphicCore::batch, 0.1f, true, false);
		//EGraphicCore::batch->draw_gabarite(*e->position_x, *e->position_y, 300.0f, 100.0f, EGraphicCore::gabarite_white_pixel);
	}
	
	//EGraphicCore::batch->draw_gabarite(0.0f, 0.0f, 100.0f, 100.0f, EGraphicCore::gabarite_white_pixel);


	EGraphicCore::batch->force_draw_call();

	ETextureAtlas::return_to_this_texture_atlas(EWindow::default_texture_atlas);

	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3( -1,  -1, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x, EGraphicCore::correction_y, 1));
	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	glBlendEquation(GL_FUNC_ADD);

	glBindTexture(GL_TEXTURE_2D, EWindow::shadow_FBO->colorbuffer);
			EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 1.0f);
			EGraphicCore::batch->draw_rect(0.0f, -500.0f, EWindow::shadow_FBO->size_x, EWindow::shadow_FBO->size_y);

	EGraphicCore::batch->force_draw_call();



	//////redraw shadowmap for entities
	ETextureAtlas::active_this_texture_atlas(EWindow::shadow_FBO, EWindow::default_texture_atlas, game_camera->position_x, game_camera->position_y, game_camera->zoom);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_MAX);

	//set correct zoom
	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	//EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3((EGraphicCore::SCR_WIDTH / 2.0f - game_camera->position_x) * EGraphicCore::correction_x - 1, (EGraphicCore::SCR_HEIGHT / 2.0f - game_camera->position_y) * EGraphicCore::correction_y - 1, 0.0f));
	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3((EGraphicCore::SCR_WIDTH / 2.0f - game_camera->position_x) * cx - 1.0f, (EGraphicCore::SCR_HEIGHT / 2.0f - game_camera->position_y + 500.0f) * cy - 1.0f, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(cx * game_camera->zoom, cy * game_camera->zoom, 1));

	//use shader
	EGraphicCore::ourShader->use();

	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));
	EGraphicCore::batch->setcolor(EColor::COLOR_GRAY);

	//draw_shadow_texture
	for (int i = draw_border_up; i >= draw_border_down; i--)
		for (int j = draw_border_left; j <= draw_border_right; j++)
			for (Entity* e : ECluster::clusters[j][i]->entity_list)
			{
				Entity::draw_sprite(e, EGraphicCore::batch, 0.1f, true, true);
				//EGraphicCore::batch->draw_gabarite(*e->position_x, *e->position_y, 300.0f, 100.0f, EGraphicCore::gabarite_white_pixel);
			}

	//EGraphicCore::batch->draw_gabarite(0.0f, 0.0f, 100.0f, 100.0f, EGraphicCore::gabarite_white_pixel);


	EGraphicCore::batch->force_draw_call();
	ETextureAtlas::return_to_this_texture_atlas(EWindow::default_texture_atlas);



	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, EWindow::default_texture_atlas->colorbuffer);


	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(round(EGraphicCore::SCR_WIDTH / 2.0f - game_camera->position_x) * EGraphicCore::correction_x - 1, round(EGraphicCore::SCR_HEIGHT / 2.0f - game_camera->position_y) * EGraphicCore::correction_y - 1, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x * game_camera->zoom, EGraphicCore::correction_y * game_camera->zoom, 1));

	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

}

void EWindowTest::draw_debug_draw_path()
{
	if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
		for (int i = up_path_draw; i >= down_path_draw; i--)
			for (int j = left_path_draw; j <= right_path_draw; j++)
			{
				if (EPath::block[j][i])
				{
					EGraphicCore::batch->setcolor(EColor::COLOR_ORANGE);
				}
				else
				{
					EGraphicCore::batch->setcolor_lum(EColor::COLOR_WHITE, (1.0f - EMath::clamp_value_float(EPath::path[j][i][EPath::active_buffer] / 200.0f, 0.0f, 1.0f)) * 0.9f + 0.1f);

					if (EPath::path[j][i][EPath::active_buffer] < 5)
					{
						EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
					}
				}



				EGraphicCore::batch->draw_gabarite(j * EPath::PATH_SIZE, i * EPath::PATH_SIZE, EPath::PATH_SIZE, EPath::PATH_SIZE, EGraphicCore::gabarite_white_pixel);

				if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
				{
					EGraphicCore::batch->setcolor(EColor::COLOR_ORANGE);
					EFont::active_font->draw(EGraphicCore::batch, std::to_string(EPath::path[j][i][EPath::active_buffer]), j * EPath::PATH_SIZE + 20.0f, i * EPath::PATH_SIZE + 10.0f);
				}
			}
}

void EWindowTest::draw_debug_collision()
{
	if ((EWindow::window_editor->is_active) || (false))
		for (int i = draw_border_up; i >= draw_border_down; i--)
			for (int j = draw_border_left; j <= draw_border_right; j++)
			{

				for (Entity* e : ECluster::clusters[j][i]->entity_list)
				{
					if (EWindow::window_editor->selected_entity == e)
					{
						EGraphicCore::batch->setcolor(EColor::COLOR_RED);
					}
					else
					{
						EGraphicCore::batch->setcolor(EColor::COLOR_BLUE);
					}

					EGraphicCore::batch->draw_rama(*e->position_x - *e->collision_left, *e->position_y - *e->collision_down, *e->collision_left + *e->collision_right, *e->collision_down + *e->collision_up, 2.0f / game_camera->zoom, EGraphicCore::gabarite_white_pixel);
					//EGraphicCore::batch->draw_gabarite(*e->position_x + e->body_offset_x.at(sprite_id), *e->position_y + e->body_offset_y.at(sprite_id), e->body.at(sprite_id)->size_x, e->body.at(sprite_id)->size_y, e->body.at(sprite_id));


				}
			}
}

void EWindowTest::draw_debug_entity_position()
{
	if (EWindow::window_editor->is_active)
	{
		EGraphicCore::batch->setcolor(EColor::COLOR_PINK);
		for (int i = draw_border_up; i >= draw_border_down; i--)
			for (int j = draw_border_left; j <= draw_border_right; j++)
				for (Entity* e : ECluster::clusters[j][i]->entity_list)
				{
					EGraphicCore::batch->draw_gabarite(*e->position_x - 1.0f, *e->position_y - 1.0f, 3.0f, 3.0f, EGraphicCore::gabarite_white_pixel);

					EGraphicCore::batch->draw_gabarite(*e->position_x - 0.0f, *e->position_y - 5.0f, 1.0f, 12.0f, EGraphicCore::gabarite_white_pixel);
					EGraphicCore::batch->draw_gabarite(*e->position_x - 5.0f, *e->position_y - 0.0f, 12.0f, 1.0f, EGraphicCore::gabarite_white_pixel);
				}
	}
}

void EWindowTest::draw_debug_cluster_border()
{
	if (EWindow::window_editor->is_active)
	{
		EGraphicCore::batch->setcolor_alpha(EColor::COLOR_GREEN, 0.55f);
		EGraphicCore::batch->draw_gabarite(draw_border_left * ECluster::CLUSTER_SIZE, draw_border_down * ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor_alpha(EColor::COLOR_RED, 0.55f);
		EGraphicCore::batch->draw_gabarite(draw_border_right * ECluster::CLUSTER_SIZE, draw_border_up * ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, EGraphicCore::gabarite_white_pixel);
	}
}

void EWindowTest::draw_debug_cluster_rama()
{
	//if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	if (EWindow::window_editor->is_active)
		for (int i = draw_border_up; i >= draw_border_down; i--)
			for (int j = draw_border_left; j <= draw_border_right; j++)
			{
				EGraphicCore::batch->setcolor(EColor::COLOR_BLACK);
				EGraphicCore::batch->draw_rama(j * ECluster::CLUSTER_SIZE, i * ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, 1.0f / game_camera->zoom, EGraphicCore::gabarite_white_pixel);
			}
}

void EWindowTest::draw(float _d)
{
	add_time_process("DRAW BEGIN");
	//----------------DRAW TERRAIN AND SHADOW----------------

	EGraphicCore::ourShader->use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, EWindow::default_texture_atlas->colorbuffer);
	EGraphicCore::shadowmap->setInt("texture1", 0);

	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(round(EGraphicCore::SCR_WIDTH / 2.0f - game_camera->position_x) * EGraphicCore::correction_x - 1.0f, round(EGraphicCore::SCR_HEIGHT / 2.0f - game_camera->position_y) * EGraphicCore::correction_y - 1.0f, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x * game_camera->zoom, EGraphicCore::correction_y * game_camera->zoom, 1));
	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);

	if (true)
	for (int i = up_path_draw; i >= down_path_draw; i--)
	for (int j = left_path_draw; j <= right_path_draw; j++)
	{EGraphicCore::batch->draw_gabarite(j * EPath::PATH_SIZE - 0.0f, i * EPath::PATH_SIZE - 0.0f, EPath::PATH_SIZE + 0.0f, EPath::PATH_SIZE + 0.0f, terrain_textures_list.at(terrain[j][i]));}

	draw_shadows();
	add_time_process("draw terrain and shadows");
	//----------------DRAW PATH MATRIX----------------
	draw_debug_draw_path();

	//add_time_process("draw_path");
	//----------------DRAW ENTITIES----------------

	//draw borders
	draw_debug_cluster_border();

	//cluster rama draw
	draw_debug_cluster_rama();


	//draw entities to shadowmap batcher
	EGraphicCore::shadowmap->use();
	EGraphicCore::batch_shadowmap->setcolor(EColor::COLOR_WHITE);

	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(round(EGraphicCore::SCR_WIDTH / 2.0f - game_camera->position_x) * EGraphicCore::correction_x - 1.0f, round(EGraphicCore::SCR_HEIGHT / 2.0f - game_camera->position_y) * EGraphicCore::correction_y - 1.0f, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x * game_camera->zoom, EGraphicCore::correction_y * game_camera->zoom, 1));


	EGraphicCore::batch_shadowmap->screen_w = EWindow::shadow_FBO->size_x;
	EGraphicCore::batch_shadowmap->screen_h = EWindow::shadow_FBO->size_y;
	EGraphicCore::batch_shadowmap->zoom = game_camera->zoom;

	transformLoc = glGetUniformLocation(EGraphicCore::shadowmap->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	GLint loc_x = glGetUniformLocation(EGraphicCore::shadowmap->ID, "offset_x");
	glUniform1f(loc_x, (EGraphicCore::SCR_WIDTH / 2.0f - game_camera->position_x) / EWindow::shadow_FBO->size_x);

	GLint loc_y = glGetUniformLocation(EGraphicCore::shadowmap->ID, "offset_y");
	glUniform1f(loc_y, (EGraphicCore::SCR_HEIGHT / 2.0f - game_camera->position_y + 500.0f) / EWindow::shadow_FBO->size_y);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, EWindow::default_texture_atlas->colorbuffer);
	EGraphicCore::shadowmap->setInt("texture1", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, EWindow::shadow_FBO->colorbuffer);
	EGraphicCore::shadowmap->setInt("texture2", 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	std::vector<Entity*> draw_sort_buffer;
	//y-sort

	add_time_process("DRAW BUFFER BEGIN");
	for (int i = draw_border_up; i >= draw_border_down; i--)
	{
		draw_sort_buffer.clear();

		for (int j = draw_border_left; j <= draw_border_right; j++)
		{
			for (Entity* e : ECluster::clusters[j][i]->entity_list)
			{
				draw_sort_buffer.push_back(e);
			}
		}
		//add_time_process("fill buffer #" + std::to_string(i));

		bool any_swap = true;

		int swap_begin = 0;
		while (any_swap)
		{
			any_swap = false;

			for (int k = draw_sort_buffer.size() - 2; k >= swap_begin; k--)
			//if (!*draw_sort_buffer.at(k + 1)->is_bullet)
			{
				Entity* e_a = draw_sort_buffer.at(k);
				Entity* e_b = draw_sort_buffer.at(k + 1);

				if (*e_a->position_y < *e_b->position_y)
				{
					draw_sort_buffer.at(k) = e_b;
					draw_sort_buffer.at(k + 1) = e_a;

					any_swap = true;
				}
			}

			swap_begin++;
		}

		//add_time_process("sort buffer #" + std::to_string(i));

		for (Entity* dsb : draw_sort_buffer)
		{
			int sprite_id = 0;
			EGraphicCore::batch_shadowmap->setcolor(EColor::COLOR_WHITE);

			Entity::draw_sprite(dsb, EGraphicCore::batch_shadowmap, _d, false, false);
		}

		//add_time_process("draw buffer #" + std::to_string(i));
	}
	add_time_process("draw buffer");
	EGraphicCore::batch_shadowmap->force_draw_call_shadowmap();

	EGraphicCore::ourShader->use();
	EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, EWindow::default_texture_atlas->colorbuffer);
	EGraphicCore::ourShader->setInt("texture1", 0);

	EGraphicCore::batch->force_draw_call();

	add_time_process("draw call buffer");

	draw_debug_collision();
	draw_debug_entity_position();

	


	




	if (!EWindow::window_editor->is_active)
	{
		EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);
		EGraphicCore::batch->draw_gabarite
		(
			crosshair_pos_x - 3.0f,
			crosshair_pos_y - 3.0f,
			7.0f,
			7.0f,
			EGraphicCore::gabarite_white_pixel
		);
	}

	/*
	EFont::active_font->draw_with_background
	(
		"angle: " + std::to_string(*link_to_player->target_angle_id),
		EGraphicCore::batch,
		*link_to_player->position_x + 100.0f,
		*link_to_player->position_y,
		EColor::COLOR_LIGHT_GRAY,
		EColor::COLOR_DARK_GRAY
	);*/


	if (glfwGetKey(EWindow::main_window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		Batcher::skew_factor += EWindowEditor::get_move_multiplier(1.0f) * _d;

		EFont::active_font->draw_with_background
		(
			"skew: " + std::to_string(Batcher::skew_factor),
			EGraphicCore::batch,
			ECamera::get_world_position_x(game_camera),
			ECamera::get_world_position_y(game_camera),
			EColor::COLOR_LIGHT_GRAY,
			EColor::COLOR_DARK_GRAY
		);
	}
	if (glfwGetKey(EWindow::main_window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		Batcher::skew_factor -= EWindowEditor::get_move_multiplier(1.0f) * _d;

		EFont::active_font->draw_with_background
		(
			"skew: " + std::to_string(Batcher::skew_factor),
			EGraphicCore::batch,
			ECamera::get_world_position_x(game_camera),
			ECamera::get_world_position_y(game_camera),
			EColor::COLOR_LIGHT_GRAY,
			EColor::COLOR_DARK_GRAY
		);
	}

	
	/*EGraphicCore::batch->setcolor(EColor::COLOR_BLACK);
	EGraphicCore::batch->draw_gabarite(100.0f + rand() % 10, 200.0f, 512.0f, 64.0f, EGraphicCore::gabarite_white_pixel);*/
}

void EWindowTest::draw_interface(float _d)
{
	


	EGraphicCore::batch->setcolor(EColor::COLOR_DARK_GRAY);
	EGraphicCore::batch->draw_gabarite(5.0f, 5.0f, 200.0f, 20.0f, EGraphicCore::gabarite_white_pixel);

	EGraphicCore::batch->setcolor(EColor::COLOR_LIGHT_GRAY);
	EFont::active_font->draw(EGraphicCore::batch, std::to_string(round(1.0f / _d)), 7.0f, 7.0f);

	EGraphicCore::batch->setcolor(EColor::COLOR_DARK_GRAY);
	EGraphicCore::batch->draw_gabarite(250.0f, 5.0f, 200.0f, 20.0f, EGraphicCore::gabarite_white_pixel);
	EGraphicCore::batch->setcolor(EColor::COLOR_LIGHT_GRAY);
	EFont::active_font->draw(EGraphicCore::batch, std::to_string(crosshair_add_x), 257.0f, 7.0f);

	EGraphicCore::batch->setcolor(EColor::COLOR_DARK_GRAY);
	EGraphicCore::batch->draw_gabarite(450.0f, 5.0f, 200.0f, 20.0f, EGraphicCore::gabarite_white_pixel);
	EGraphicCore::batch->setcolor(EColor::COLOR_LIGHT_GRAY);
	EFont::active_font->draw(EGraphicCore::batch, std::to_string(crosshair_add_y), 457.0f, 7.0f);

	if (time_process_active)
	{
		float time_process_h = 0;

		for (int i = 0; i < EWindow::time_process_name.size(); i++)
		{
			EGraphicCore::batch->setcolor_alpha(EColor::COLOR_BLACK, 0.9f);
			EGraphicCore::batch->draw_gabarite(0.0f, EGraphicCore::SCR_HEIGHT - 22.0f - i * 25.0f, 300.0f, 20.0f, EGraphicCore::gabarite_white_pixel);

			EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 0.9f);
			EFont::active_font->draw(EGraphicCore::batch, EWindow::time_process_name.at(i), 5.0f, EGraphicCore::SCR_HEIGHT - 22.0f - i * 25.0f + 3.0f);
			EFont::active_font->draw(EGraphicCore::batch, std::to_string(EWindow::time_process_value.at(i)), 205.0f, EGraphicCore::SCR_HEIGHT - 22.0f - i * 25.0f + 3.0f);
		}
	}

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		EGraphicCore::batch->reinit();
		EGraphicCore::batch->draw_call();
		EGraphicCore::batch->reset();
		

		glBindTexture(GL_TEXTURE_2D, EWindow::shadow_FBO->colorbuffer);
		EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 1.0f);
		EGraphicCore::batch->draw_rect(0.0f, 0.0f, EWindow::shadow_FBO->size_x, EWindow::shadow_FBO->size_y);

		EGraphicCore::batch->reinit();
		EGraphicCore::batch->draw_call();
		EGraphicCore::batch->reset();
		

		glBindTexture(GL_TEXTURE_2D, EWindow::default_texture_atlas->colorbuffer);

	}
}

void EWindowTest::generate_terrain()
{
	for (int j=0; j<EPath::PATH_DIM; j++)
	for (int i=0; i<EPath::PATH_DIM; i++)
	{
		terrain[j][i] = rand() % 5;
	}
}
