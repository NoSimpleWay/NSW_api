#pragma once
#include "EWindowTest.h"

#include "EWindowEditor.h"
#include "EBA.h"


std::string s;

int maximum_alloy = 0;

float EWindowTest::blur_factor = 0.525f;//0.33333
float EWindowTest::blur_blend = 0.55f; //1.0f;
float EWindowTest::blur_decay_flat_factor = 0.0017f;//0.002
float EWindowTest::add_factor = 1.0000f;

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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	ETextureAtlas::active_this_texture_atlas(EWindow::lightmap_FBO, EWindow::default_texture_atlas);
	glClear(GL_COLOR_BUFFER_BIT);

	ETextureAtlas::active_this_texture_atlas(EWindow::lightmap_FBO2, EWindow::default_texture_atlas);
	glClear(GL_COLOR_BUFFER_BIT);

	ETextureAtlas::return_to_this_texture_atlas(default_texture_atlas);

	terrain_200 = ETextureAtlas::put_texture_to_atlas("data/textures/terrain_200.png", EWindow::default_texture_atlas);
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
	if (glfwGetKey(EWindow::main_window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		_d /= 10.0f;
	}
	add_time_process("UPDATE BEGIN");

	day_time += _d/1000.0f;

	if (day_time > 2.0f)
	{
		day_time -= 2.0f;
	}

	Batcher::skew_factor = EMath::clamp_value_float(day_time, 0.0f, 1.0f);

	if ((!EWindow::window_editor->is_active)||(true))
	{

		if (Batcher::skew_factor <= 0.1f)
		{
			EColor::get_interpolate_color(EColor::COLOR_SKY_TIME_SUNSET, EColor::COLOR_SKY_TIME_DAWN, Batcher::skew_factor * 10.0f, EColor::COLOR_SKY_AMBIENT);
		}
		else if (Batcher::skew_factor <= 0.2f)
		{
			EColor::get_interpolate_color(EColor::COLOR_SKY_TIME_DAWN, EColor::COLOR_SKY_TIME_NOON, (Batcher::skew_factor - 0.1f) * 10.0f, EColor::COLOR_SKY_AMBIENT);
		}
		else if (Batcher::skew_factor >= 0.8f)
		{
			EColor::get_interpolate_color(EColor::COLOR_SKY_TIME_NOON, EColor::COLOR_SKY_TIME_SUNSET, (Batcher::skew_factor - 0.8f) * 5.0f, EColor::COLOR_SKY_AMBIENT);
		}
		else
		{
			EColor::apply_color(EColor::COLOR_SKY_AMBIENT, EColor::COLOR_SKY_TIME_NOON);
		}

		if (Batcher::skew_factor <= 0.1f)
		{
			EColor::get_interpolate_color(EColor::COLOR_SHADOW_TIME_SUNSET, EColor::COLOR_SHADOW_TIME_DAWN, Batcher::skew_factor * 10.0f, EColor::COLOR_LAZURE_SHADOW);
		}
		else
			if (Batcher::skew_factor <= 0.2f)
			{
				EColor::get_interpolate_color(EColor::COLOR_SHADOW_TIME_DAWN, EColor::COLOR_SHADOW_TIME_NOON, (Batcher::skew_factor - 0.1f) * 10.0f, EColor::COLOR_LAZURE_SHADOW);
			}
			else
				if (Batcher::skew_factor >= 0.8f)
				{
					EColor::get_interpolate_color(EColor::COLOR_SHADOW_TIME_NOON, EColor::COLOR_SHADOW_TIME_SUNSET, (Batcher::skew_factor - 0.8f) * 5.0f, EColor::COLOR_LAZURE_SHADOW);
				}
				else
				{
					EColor::apply_color(EColor::COLOR_LAZURE_SHADOW, EColor::COLOR_SHADOW_TIME_NOON);
				}
	}
	//glfwGetCursorPos(EWindow::main_window, &EWindow::mouse_x, &EWindow::mouse_y);
	else
	{
		EColor::apply_color(EColor::COLOR_SKY_AMBIENT, EColor::COLOR_WHITE);
		EColor::apply_color(EColor::COLOR_LAZURE_SHADOW, EColor::COLOR_LIGHT_GRAY);
	}

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


	bool any_button_overlap = false;

	for (EWindow* w:EWindow::window_list)
	if (w->is_active)
	for (EButton* b : w->button_list)
	if ((b->is_active) & (b->is_overlap()))
	{
		any_button_overlap = true; break;
	}

	if (!any_button_overlap)
	{
		if (EWindow::scroll > 0) game_camera->zoom /= 0.5f;
		if (EWindow::scroll < 0) game_camera->zoom *= 0.5f;
	}

	if ((EWindow::window_editor->is_active) & (!EButton::any_input))
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





	if (EWindow::window_editor->is_active)
	{
		game_camera->position_x = free_camera_x * game_camera->zoom;
		game_camera->position_y = free_camera_y * game_camera->zoom;
	}




	

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

		*e->saved_eb_x = (int)(*e->position_x / EPath::PATH_SIZE);
		*e->saved_eb_y = (int)(*e->position_y / EPath::PATH_SIZE);
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

	for (int i = update_border_up;		i >= update_border_down;	i--)
	for (int j = update_border_left;	j <= update_border_right;	j++)
	for (Entity* e : ECluster::clusters[j][i]->entity_list)
	//if (!*e->already_updated)
	if ((!*e->inmovable) & (!*e->is_bullet))
	{
		//clear block
		if ((*e->saved_eb_x >= 0) & (*e->saved_eb_y >= 0))
		{
			EPath::entity_block[*e->saved_eb_x][*e->saved_eb_y] = false;
		}
	}

	add_time_process("path entity unblock");



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

		if (*e->controlled_by_player)
		{
			int speed_mul = 1;
			if
			(
				(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				||
				(glfwGetKey(EWindow::main_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
			)
			{
				speed_mul = 10;
			}
			if (glfwGetKey(EWindow::main_window, GLFW_KEY_A) == GLFW_PRESS) {dir_x = -1 * speed_mul;}

			if (glfwGetKey(EWindow::main_window, GLFW_KEY_D) == GLFW_PRESS)	{dir_x = 1 * speed_mul;}

			if (glfwGetKey(EWindow::main_window, GLFW_KEY_S) == GLFW_PRESS)	{dir_y = -1 * speed_mul;}

			if (glfwGetKey(EWindow::main_window, GLFW_KEY_W) == GLFW_PRESS) {dir_y = 1 * speed_mul;}

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

					*bullet->mass_pointer = 0.1;

					*bullet->is_bullet = true;

					

					bullet->action_on_hit = &Entity::test_hit_action_self_destroy_on_hit;

					*bullet->have_light_source = true;
					*bullet->light_source_red = 1.0f;
					*bullet->light_source_green = 0.8f;
					*bullet->light_source_blue = 0.7f;

					
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

					*bullet->speed_x += 2000.0f * mul_x;
					*bullet->speed_y += 2000.0f * mul_y;



					*bullet->real_speed_x = *bullet->speed_x * _d;
					*bullet->real_speed_y = *bullet->speed_y * _d;

					ESprite* spr = new ESprite();

					bullet->sprite_list.push_back(spr);

					bullet->sprite_list.at(0)->sprite_struct_list.at(0)->gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/bullet.png", EWindow::default_texture_atlas);
					bullet->sprite_list.at(0)->sprite_struct_list.at(0)->supermap = ETextureAtlas::put_texture_to_atlas("data/textures/bullet.png", EWindow::default_texture_atlas);
					
					*bullet->sprite_list.at(0)->sprite_struct_list.at(0)->offset_x = -26.0f;
					*bullet->sprite_list.at(0)->sprite_struct_list.at(0)->offset_y = -26.0f;
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

		if (*e->controlled_by_ai)
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



			e->target = link_to_player;

			*e->search_cooldown -= _d;

				if (*e->search_cooldown <= 0)
				{
					*e->search_cooldown += 0.5f;

					if (Entity::can_see(e, link_to_player, _d))
					{
						*e->is_see_target = true;
						float dst_x = *e->position_x - *link_to_player->position_x;
						float dst_y = *e->position_y - *link_to_player->position_y;

						if (dst_x * dst_x + dst_y * dst_y < 250000.0f)
						{*e->random_move_timer = 1.0f;}
						else
						{
							*e->random_move_timer = 0.0f;
						}
					}
					else
					{
						*e->is_see_target = false;
					}
				}

			if (*e->random_move_timer >= 0)
			{
				*e->random_move_timer -= _d;

				dir_x = *e->random_direction_x;
				dir_y = *e->random_direction_y;
			}

			*e->random_move_cooldown -= _d;
			if (*e->random_move_cooldown <= 0)
			{
				*e->random_move_cooldown += 1.25f;

				*e->random_direction_x = rand() % 3 - 1;
				*e->random_direction_y = rand() % 3 - 1;
			}


			
		}//end block of ai actions

		//add_time_process("entities_path_find");
		if (dir_x * dir_y != 0) 	{dir_mul = 0.7f;}
		*e->speed_x += dir_x * _d * 3330.0f * dir_mul;
		*e->speed_y += dir_y * _d * 3330.0f * dir_mul;

		*e->real_speed_x = *e->speed_x * _d;
		*e->real_speed_y = *e->speed_y * _d;




	}


		////
		////===>
		////

	add_time_process("entity control");



		bool need_second_move_update = true;

		

		for (int u = 0; u < 2; u++)
		if ((u == 0)||(need_second_move_update))
		{

			for (int i = update_border_up;		i >= update_border_down; i--)
			for (int j = update_border_left;	j <= update_border_right; j++)
			for (Entity* e : ECluster::clusters[j][i]->entity_list)
			//if (!*e->already_updated)
				if ((!*e->inmovable) & (!*e->is_ghost))
				{
					*e->real_speed_x = *e->speed_x * _d;
					*e->real_speed_y = *e->speed_y * _d;

					Entity::collision_process(e, _d);


				//std::cout << "-------BONK!-------" << std::endl;
	



				if ((!*e->is_bullet) && (u == 0))
				{
					*e->speed_x *= pow(0.005, _d);
					*e->speed_y *= pow(0.005, _d);
				}


				int new_cluster_x = (int)(*e->position_x / ECluster::CLUSTER_SIZE);
				int new_cluster_y = (int)(*e->position_y / ECluster::CLUSTER_SIZE);

				if ((new_cluster_x != *e->prev_cluster_x) || (new_cluster_y != *e->prev_cluster_y))
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

		if (link_to_player != NULL)
			//if (!glfwGetKey(EWindow::main_window, GLFW_KEY_SPACE) == GLFW_PRESS)
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
		game_camera->position_x = round(game_camera->position_x);
		game_camera->position_y = round(game_camera->position_y);

		//----------------TERRAIN MATRIX GABARITES----------------
		left_terrain_draw = (int)((game_camera->position_x / game_camera->zoom - EGraphicCore::SCR_WIDTH / 2.0f / game_camera->zoom) / EPath::PATH_SIZE) - 0; if (left_terrain_draw < 0) { left_terrain_draw = 0; }
		right_terrain_draw = (int)((game_camera->position_x / game_camera->zoom + EGraphicCore::SCR_WIDTH / 2.0f / game_camera->zoom) / EPath::PATH_SIZE) + 0; if (right_terrain_draw >= EPath::PATH_DIM) { right_terrain_draw = EPath::PATH_DIM - 1; }

		down_terrain_draw = (int)((game_camera->position_y / game_camera->zoom - EGraphicCore::SCR_HEIGHT / 2.0f / game_camera->zoom) / EPath::PATH_SIZE) - 0; if (down_terrain_draw < 0) { down_terrain_draw = 0; }
		up_terrain_draw = (int)((game_camera->position_y / game_camera->zoom + EGraphicCore::SCR_HEIGHT / 2.0f / game_camera->zoom) / EPath::PATH_SIZE) + 0; if (up_terrain_draw >= EPath::PATH_DIM) { up_terrain_draw = EPath::PATH_DIM - 1; }


		//----------------PATH MATRIX GABARITES----------------
		left_path_draw = (int)((game_camera->position_x / game_camera->zoom - EGraphicCore::SCR_WIDTH / 2.0f / game_camera->zoom) / EPath::PATH_SIZE) - 10; if (left_path_draw < 0) { left_path_draw = 0; }
		right_path_draw = (int)((game_camera->position_x / game_camera->zoom + EGraphicCore::SCR_WIDTH / 2.0f / game_camera->zoom) / EPath::PATH_SIZE) + 10; if (right_path_draw >= EPath::PATH_DIM) { right_path_draw = EPath::PATH_DIM - 1; }

		down_path_draw = (int)((game_camera->position_y / game_camera->zoom - EGraphicCore::SCR_HEIGHT / 2.0f / game_camera->zoom) / EPath::PATH_SIZE) - 10; if (down_path_draw < 0) { down_path_draw = 0; }
		up_path_draw = (int)((game_camera->position_y / game_camera->zoom + EGraphicCore::SCR_HEIGHT / 2.0f / game_camera->zoom) / EPath::PATH_SIZE) + 10; if (up_path_draw >= EPath::PATH_DIM) { up_path_draw = EPath::PATH_DIM - 1; }

		//----------------DRAW BORDER GABARITES----------------
		draw_border_left = (int)((game_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f) / game_camera->zoom / ECluster::CLUSTER_SIZE) - 1; if (draw_border_left < 0) { draw_border_left = 0; }
		draw_border_right = (int)((game_camera->position_x + EGraphicCore::SCR_WIDTH / 2.0f) / game_camera->zoom / ECluster::CLUSTER_SIZE) + 1; if (draw_border_right >= ECluster::CLUSTER_DIM) { draw_border_right = ECluster::CLUSTER_DIM - 1;; }

		draw_border_down = (int)((game_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f) / game_camera->zoom / ECluster::CLUSTER_SIZE) - 1; if (draw_border_down < 0) { draw_border_down = 0; }
		draw_border_up = (int)((game_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f) / game_camera->zoom / ECluster::CLUSTER_SIZE) + 1; if (draw_border_up >= ECluster::CLUSTER_DIM) { draw_border_up = ECluster::CLUSTER_DIM - 1; }


}

void EWindowTest::default_draw(float _d)
{
}

void EWindowTest::draw_shadows()
{

	//draw call terrain

	EGraphicCore::batch->reset();

	//active shadow FBO
	ETextureAtlas::active_this_texture_atlas(EWindow::shadow_ground_FBO, EWindow::default_texture_atlas);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_MAX);
	float scx = (EGraphicCore::SCR_WIDTH / EWindow::shadow_ground_FBO->size_x);
	float scy = (EGraphicCore::SCR_HEIGHT / EWindow::shadow_ground_FBO->size_y);

	float	cx = 1.0f / EGraphicCore::SCR_WIDTH * 2.0f * scx;
	float	cy = 1.0f / EGraphicCore::SCR_HEIGHT * 2.0f * scy;





	//set correct zoom
	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	//EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3((EGraphicCore::SCR_WIDTH / 2.0f - game_camera->position_x) * EGraphicCore::correction_x - 1, (EGraphicCore::SCR_HEIGHT / 2.0f - game_camera->position_y) * EGraphicCore::correction_y - 1, 0.0f));
	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3((EGraphicCore::SCR_WIDTH / 2.0f - game_camera->position_x) * cx - 1.0f, (EGraphicCore::SCR_HEIGHT / 2.0f - game_camera->position_y) * cy - 1.0f, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(cx * game_camera->zoom, cy * game_camera->zoom, 1));

	//use shader
	EGraphicCore::ourShader->use();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//

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


	/*glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	glBlendEquation(GL_FUNC_ADD);

	glBindTexture(GL_TEXTURE_2D, EWindow::shadow_FBO->colorbuffer);
			EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 1.0f);
			EGraphicCore::batch->draw_rect(0.0f, -500.0f, EWindow::shadow_FBO->size_x, EWindow::shadow_FBO->size_y);

	EGraphicCore::batch->force_draw_call();*/



	//////redraw shadowmap for entities
	ETextureAtlas::active_this_texture_atlas(EWindow::shadow_FBO, EWindow::default_texture_atlas);
	glClearColor(EColor::COLOR_LAZURE_SHADOW->color_red, EColor::COLOR_LAZURE_SHADOW->color_green, EColor::COLOR_LAZURE_SHADOW->color_blue, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_MAX);

	scx = (EGraphicCore::SCR_WIDTH / EWindow::shadow_FBO->size_x);
	scy = (EGraphicCore::SCR_HEIGHT / EWindow::shadow_FBO->size_y);
	cx = 1.0f / EGraphicCore::SCR_WIDTH * 2.0f * scx;
	cy = 1.0f / EGraphicCore::SCR_HEIGHT * 2.0f * scy;
	//set correct zoom
	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	//EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3((EGraphicCore::SCR_WIDTH / 2.0f - game_camera->position_x) * EGraphicCore::correction_x - 1, (EGraphicCore::SCR_HEIGHT / 2.0f - game_camera->position_y) * EGraphicCore::correction_y - 1, 0.0f));
	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3((round(EGraphicCore::SCR_WIDTH / 2.0f) - game_camera->position_x) * cx - 1.0f, (round(EGraphicCore::SCR_HEIGHT / 2.0f) - game_camera->position_y + 500.0f) * cy - 1.0f, 0.0f));
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

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


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
					if (*EWindow::window_editor->entity_gabarite_mode_active == EWindowEditor::EntityGabariteMode::EntityGabariteCollision)
					{
						
						if (*e->is_ghost)
						{EGraphicCore::batch->setcolor_alpha(EColor::COLOR_BLUE, 0.35f);}
						else
						{EGraphicCore::batch->setcolor(EColor::COLOR_BLUE);}

						if (EWindow::window_editor->selected_entity == e)
						{EGraphicCore::batch->draw_rama(*e->position_x - *e->collision_left, *e->position_y - *e->collision_down, *e->collision_left + *e->collision_right, *e->collision_down + *e->collision_up, 3.0f / game_camera->zoom, EGraphicCore::gabarite_white_pixel);}
						else
						{EGraphicCore::batch->draw_rama(*e->position_x - *e->collision_left, *e->position_y - *e->collision_down, *e->collision_left + *e->collision_right, *e->collision_down + *e->collision_up, 1.0f / game_camera->zoom, EGraphicCore::gabarite_white_pixel);}
						//EGraphicCore::batch->draw_gabarite(*e->position_x + e->body_offset_x.at(sprite_id), *e->position_y + e->body_offset_y.at(sprite_id), e->body.at(sprite_id)->size_x, e->body.at(sprite_id)->size_y, e->body.at(sprite_id));
					}

					if (*EWindow::window_editor->entity_gabarite_mode_active == EWindowEditor::EntityGabariteMode::EntityGabaritePathBlock)
					{
						
						if (*e->no_path_block)
						{EGraphicCore::batch->setcolor_alpha(EColor::COLOR_ORANGE, 0.35f);}
						else
						{EGraphicCore::batch->setcolor(EColor::COLOR_ORANGE);}

						if (EWindow::window_editor->selected_entity == e)
						{EGraphicCore::batch->draw_rama(*e->position_x - *e->path_block_gabarite_left, *e->position_y - *e->path_block_gabarite_down, *e->path_block_gabarite_left + *e->path_block_gabarite_right, *e->path_block_gabarite_down + *e->path_block_gabarite_up, 3.0f / game_camera->zoom, EGraphicCore::gabarite_white_pixel);}
						else
						{EGraphicCore::batch->draw_rama(*e->position_x - *e->path_block_gabarite_left, *e->position_y - *e->path_block_gabarite_down, *e->path_block_gabarite_left + *e->path_block_gabarite_right, *e->path_block_gabarite_down + *e->path_block_gabarite_up, 1.0f / game_camera->zoom, EGraphicCore::gabarite_white_pixel);}
						//EGraphicCore::batch->draw_gabarite(*e->position_x + e->body_offset_x.at(sprite_id), *e->position_y + e->body_offset_y.at(sprite_id), e->body.at(sprite_id)->size_x, e->body.at(sprite_id)->size_y, e->body.at(sprite_id));
					}
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

void EWindowTest::draw_terrain()
{
	EGraphicCore::batch_terrain->reset();
	ETextureAtlas::return_to_this_texture_atlas(EWindow::default_texture_atlas);
	//----------------DRAW TERRAIN AND SHADOW----------------

	//EGraphicCore::batch_terrain->force_draw_call_terrain
	EGraphicCore::shader_terrain->use();




	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, EWindow::default_texture_atlas->colorbuffer);
	EGraphicCore::shader_terrain->setInt("texture1", 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, EWindow::lightmap_FBO->colorbuffer);
	EGraphicCore::shader_terrain->setInt("texture2", 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, EWindow::shadow_ground_FBO->colorbuffer);
	EGraphicCore::shader_terrain->setInt("texture3", 2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//

	GLint loc_x = glGetUniformLocation(EGraphicCore::shader_terrain->ID, "screen_size_x");
	glUniform1f(loc_x, EGraphicCore::SCR_WIDTH  / EWindow::shadow_ground_FBO->size_x);

	GLint loc_y = glGetUniformLocation(EGraphicCore::shader_terrain->ID, "screen_size_y");
	glUniform1f(loc_y, (EGraphicCore::SCR_HEIGHT + 000.0f) / (EWindow::shadow_ground_FBO->size_y));

	GLint ambient_loc = glGetUniformLocation(EGraphicCore::shader_terrain->ID, "ambient_color");
	glUniform4f(ambient_loc, EColor::COLOR_SKY_AMBIENT->color_red, EColor::COLOR_SKY_AMBIENT->color_green, EColor::COLOR_SKY_AMBIENT->color_blue, 1.0f);
	//glUniform4f(ambient_loc, EColor::COLOR_SKY_AMBIENT->color_red * 0.0f, EColor::COLOR_SKY_AMBIENT->color_green, EColor::COLOR_SKY_AMBIENT->color_blue, 1.0f);

	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(((EGraphicCore::SCR_WIDTH / 2.0f) - game_camera->position_x) * EGraphicCore::correction_x - 1.0f, ((EGraphicCore::SCR_HEIGHT / 2.0f) - game_camera->position_y) * EGraphicCore::correction_y - 1.0f, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x * game_camera->zoom, EGraphicCore::correction_y * game_camera->zoom, 1));
	transformLoc = glGetUniformLocation(EGraphicCore::shader_terrain->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	EGraphicCore::batch_terrain->setcolor(EColor::COLOR_WHITE);

	if (false)
		for (int i = draw_border_up; i >= draw_border_down; i--)
			for (int j = draw_border_left; j <= draw_border_right; j++)
			{
				EGraphicCore::batch_terrain->draw_terrain
				(
					j * ECluster::CLUSTER_SIZE,
					i * ECluster::CLUSTER_SIZE,
					terrain_200
				);
			}



	if (true)
		for (int i = up_terrain_draw; i >= down_terrain_draw; i--)
			for (int j = left_terrain_draw; j <= right_terrain_draw; j++)
			{
				EGraphicCore::batch_terrain->draw_terrain(j * EPath::PATH_SIZE * 1.0f, i * EPath::PATH_SIZE * 1.0f, terrain_textures_list.at(terrain[j][i]));
			}

	EGraphicCore::batch_terrain->force_draw_call_terrain();
}

void EWindowTest::draw_lightmap()
{
	//draw lightmap
	EGraphicCore::batch->reset();
	EGraphicCore::ourShader->use();

	ETextureAtlas::active_this_texture_atlas(EWindow::base_lightmap, EWindow::default_texture_atlas);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f, -1.0f, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(1.0f / 150.0f, 1.0f / 150.0f, 1));

	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	glBlendFunc(GL_ONE, GL_ONE);
	if (true)
		for (int i = draw_border_down; i <= draw_border_up; i++)
			for (int j = draw_border_left; j <= draw_border_right; j++)
				for (Entity* e : ECluster::clusters[j][i]->entity_list)
					if (*e->have_light_source)
					{
						EGraphicCore::batch->setcolor(*e->light_source_red, *e->light_source_green, *e->light_source_blue, 1.0f);
						if (*e->is_bullet)
						{EGraphicCore::batch->draw_gabarite(round(*e->position_x / 40.0f) - 0.0f, round(*e->position_y / 40.0f) - 0.0f, 1.0f, 1.0f, EGraphicCore::gabarite_white_pixel);}
						else
						{EGraphicCore::batch->draw_gabarite(round(*e->position_x / 40.0f) - 1.0f, round(*e->position_y / 40.0f) - 1.0f, 3.0f, 3.0f, EGraphicCore::gabarite_white_pixel);}

					}

	EGraphicCore::batch->force_draw_call();
	add_time_process("draw lights");

	ETextureAtlas::active_this_texture_atlas(EWindow::base_blockmap, EWindow::default_texture_atlas);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	EGraphicCore::batch->setcolor_lum(EColor::COLOR_BLACK, 1.0f);
	for (int i = down_terrain_draw; i <= up_terrain_draw; i++)
	for (int j = left_terrain_draw; j <= right_terrain_draw; j++)
	if (EPath::block[j][i])
	{
		EGraphicCore::batch->draw_gabarite(j, i, 1.0f, 1.0f, EGraphicCore::gabarite_white_pixel);
	}

	EGraphicCore::batch->force_draw_call();
	add_time_process("draw block");

	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	EGraphicCore::batch->reset();
	EGraphicCore::batch->setcolor_lum(EColor::COLOR_WHITE, 1.0f);
		//spread lightmap
		//put lightmap
			EGraphicCore::ourShader->use();
			ETextureAtlas::active_this_texture_atlas(EWindow::lightmap_FBO, EWindow::base_lightmap);
			transformLoc = glGetUniformLocation(EGraphicCore::lightmap_blur->ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));


			//glBlendEquation(GL_MAX);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//glBlendFunc(GL_ONE, GL_ONE);
			//glBlendFunc(GL_ONE, GL_ONE);
			for (int i = 0; i < 1; i++)
			{
				EGraphicCore::batch->draw_rect(0.0f, 0.0f, 300.0f, 300.0f);
				EGraphicCore::batch->force_draw_call();
			}

			
			glBlendEquation(GL_FUNC_ADD);
			/*EGraphicCore::batch->setcolor_lum(EColor::COLOR_WHITE, 1.0f);
			EGraphicCore::ourShader->use();//draw blockmap
			glBlendFunc(GL_ZERO, GL_SRC_COLOR);
			transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));
			ETextureAtlas::active_this_texture_atlas(EWindow::lightmap_FBO, EWindow::base_blockmap);
			EGraphicCore::batch->draw_rect(0.0f, 0.0f, 300.0f, 300.0f);
			EGraphicCore::batch->force_draw_call();*/

	//blur lightmap

			EGraphicCore::batch->setcolor_lum(EColor::COLOR_WHITE, 1.0f);
		
			GLint blur_loc = glGetUniformLocation(EGraphicCore::lightmap_blur->ID, "blur");
			GLint decay_mul = glGetUniformLocation(EGraphicCore::lightmap_blur->ID, "decay_mul");
			GLint decay_flat = glGetUniformLocation(EGraphicCore::lightmap_blur->ID, "decay_flat");
			glUniform1f(blur_loc, add_factor);
	//glBlendFunc(GL_ONE, GL_ZERO);
	for (int i = 0; i < 4; i++)
	{


			EGraphicCore::lightmap_blur->use();
				glUniform1f(blur_loc, blur_factor);
				glUniform1f(decay_mul, blur_blend);
				glUniform1f(decay_flat, blur_decay_flat_factor);
			transformLoc = glGetUniformLocation(EGraphicCore::lightmap_blur->ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

			ETextureAtlas::active_this_texture_atlas(EWindow::lightmap_FBO2, EWindow::lightmap_FBO);
			EGraphicCore::lightmap_blur->setInt("texture1", 0);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, EWindow::base_blockmap->colorbuffer);
			EGraphicCore::lightmap_blur->setInt("texture2", 1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			EGraphicCore::batch->draw_rect(0.0f, 0.0f, 300.0f, 300.0f);
			EGraphicCore::batch->force_draw_call();

			
			/*EGraphicCore::ourShader->use();//draw blockmap
			glBlendFunc(GL_ZERO, GL_SRC_COLOR);
			transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
			ETextureAtlas::active_this_texture_atlas(EWindow::lightmap_FBO2, EWindow::base_blockmap);
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));
			EGraphicCore::batch->draw_rect(0.0f, 0.0f, 300.0f, 300.0f);
			EGraphicCore::batch->force_draw_call();
			*/
			



			EGraphicCore::lightmap_blur->use();
				glUniform1f(blur_loc, blur_factor);
				glUniform1f(decay_mul, blur_blend);
				glUniform1f(decay_flat, blur_decay_flat_factor);
			transformLoc = glGetUniformLocation(EGraphicCore::lightmap_blur->ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

			ETextureAtlas::active_this_texture_atlas(EWindow::lightmap_FBO, EWindow::lightmap_FBO2);
			EGraphicCore::lightmap_blur->setInt("texture1", 0);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, EWindow::base_blockmap->colorbuffer);
			EGraphicCore::lightmap_blur->setInt("texture2", 1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			EGraphicCore::batch->draw_rect(0.0f, 0.0f, 300.0f, 300.0f);
			EGraphicCore::batch->force_draw_call();

			
			/*EGraphicCore::ourShader->use();//draw blockmap
			glBlendFunc(GL_ZERO, GL_SRC_COLOR);
			transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));
			ETextureAtlas::active_this_texture_atlas(EWindow::lightmap_FBO, EWindow::base_blockmap);
			EGraphicCore::batch->draw_rect(0.0f, 0.0f, 300.0f, 300.0f);
			EGraphicCore::batch->force_draw_call();*/

			/*
			EGraphicCore::ourShader->use();
			transformLoc = glGetUniformLocation(EGraphicCore::lightmap_blur->ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));
			ETextureAtlas::active_this_texture_atlas(EWindow::lightmap_FBO, EWindow::base_lightmap);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			EGraphicCore::batch->draw_rect(0.0f, 0.0f, 300.0f, 300.0f);
			EGraphicCore::batch->force_draw_call();*/


	}



}

void EWindowTest::draw(float _d)
{
	

	add_time_process("DRAW BEGIN");
	
	

	
	draw_lightmap(); add_time_process("draw lightmap");
	
	draw_shadows();	add_time_process("draw shadows");

	draw_terrain(); add_time_process("draw terrain");

	
	

	




	

	//

	







	//




	EGraphicCore::batch->reset();
	////////////////return to normal texture draw mode/////////////////
	EGraphicCore::ourShader->use();
	ETextureAtlas::return_to_this_texture_atlas(EWindow::default_texture_atlas);
	glBindTexture(GL_TEXTURE_2D, EWindow::default_texture_atlas->colorbuffer);

	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3((round(EGraphicCore::SCR_WIDTH / 2.0f) - game_camera->position_x) * EGraphicCore::correction_x - 1, (round(EGraphicCore::SCR_HEIGHT / 2.0f) - game_camera->position_y) * EGraphicCore::correction_y - 1, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x * game_camera->zoom, EGraphicCore::correction_y * game_camera->zoom, 1));

	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));
	/////////////////////////////////////////////////////////////////



	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//----------------DRAW PATH MATRIX----------------
	draw_debug_draw_path();
	draw_debug_cluster_border();
	draw_debug_cluster_rama();

	//force draw call, because switch to another batcher
	EGraphicCore::batch->force_draw_call();





	//draw entities to shadow receiver batcher
	EGraphicCore::shadowmap->use();
	EGraphicCore::batch_shadowmap->setcolor(EColor::COLOR_WHITE);

	EGraphicCore::batch_shadowmap->screen_w = EWindow::shadow_FBO->size_x;
	EGraphicCore::batch_shadowmap->screen_h = EWindow::shadow_FBO->size_y;
	EGraphicCore::batch_shadowmap->zoom = game_camera->zoom;

	transformLoc = glGetUniformLocation(EGraphicCore::shadowmap->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	GLint loc_x = glGetUniformLocation(EGraphicCore::shadowmap->ID, "offset_x");
	glUniform1f(loc_x, (round(EGraphicCore::SCR_WIDTH / 2.0f) - game_camera->position_x) / EWindow::shadow_FBO->size_x);

	GLint loc_y = glGetUniformLocation(EGraphicCore::shadowmap->ID, "offset_y");
	glUniform1f(loc_y, (round(EGraphicCore::SCR_HEIGHT / 2.0f) - game_camera->position_y + 500.0f) / EWindow::shadow_FBO->size_y);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, EWindow::default_texture_atlas->colorbuffer);
	EGraphicCore::shadowmap->setInt("texture1", 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, EWindow::shadow_FBO->colorbuffer);
	EGraphicCore::shadowmap->setInt("texture2", 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, EWindow::lightmap_FBO->colorbuffer);
	EGraphicCore::shadowmap->setInt("texture3", 2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
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


	////////////////return to normal texture draw mode/////////////////
	ETextureAtlas::return_to_this_texture_atlas(EWindow::default_texture_atlas);
	glBindTexture(GL_TEXTURE_2D, EWindow::default_texture_atlas->colorbuffer);

	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(round(EGraphicCore::SCR_WIDTH / 2.0f - game_camera->position_x) * EGraphicCore::correction_x - 1, (EGraphicCore::SCR_HEIGHT / 2.0f - game_camera->position_y) * EGraphicCore::correction_y - 1, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x * game_camera->zoom, EGraphicCore::correction_y * game_camera->zoom, 1));

	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));
	/////////////////////////////////////////////////////////////////



	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


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

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		day_time += EWindowEditor::get_move_multiplier(1.0f) * _d;
	}

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		blur_factor += EWindowEditor::get_move_multiplier(0.5f) * _d;

		EFont::active_font->draw_with_background
		(
			"blur: " + std::to_string(blur_factor),
			EGraphicCore::batch,
			ECamera::get_world_position_x(game_camera),
			ECamera::get_world_position_y(game_camera),
			EColor::COLOR_LIGHT_GRAY,
			EColor::COLOR_DARK_GRAY
		);
	}
	if (glfwGetKey(EWindow::main_window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		blur_factor -= EWindowEditor::get_move_multiplier(0.5f) * _d;

		EFont::active_font->draw_with_background
		(
			"blur: " + std::to_string(blur_factor),
			EGraphicCore::batch,
			ECamera::get_world_position_x(game_camera),
			ECamera::get_world_position_y(game_camera),
			EColor::COLOR_LIGHT_GRAY,
			EColor::COLOR_DARK_GRAY
		);
	}

	Batcher::skew_factor = EMath::clamp_value_float(Batcher::skew_factor, 0.0f, 1.0f);

	if ((EWindow::window_editor->selected_entity != NULL) & (EWindow::window_editor->is_active))
	{
		if (Entity::can_see(link_to_player, EWindow::window_editor->selected_entity, _d))
		{
			EFont::active_font->draw_with_background("see", EGraphicCore::batch, *link_to_player->position_x + 100.0f, *link_to_player->position_y + 10.0f, EColor::COLOR_DARK_GREEN, EColor::COLOR_GREEN);
		}
		else
		{
			EFont::active_font->draw_with_background("cant see", EGraphicCore::batch, *link_to_player->position_x + 100.0f, *link_to_player->position_y + 10.0f, EColor::COLOR_RED, EColor::COLOR_DARK_RED);
		}

		if (!*link_to_player->pointer_to_bool_list.at(Entity::EntityBoolAttributes::ENTITY_BOOL_ATTRIBUTE_INMOVABLE))
		{
			EFont::active_font->draw_with_background("movable", EGraphicCore::batch, *link_to_player->position_x + 200.0f, *link_to_player->position_y + 10.0f, EColor::COLOR_DARK_GREEN, EColor::COLOR_GREEN);
		}
		else
		{
			EFont::active_font->draw_with_background("inmovable", EGraphicCore::batch, *link_to_player->position_x + 200.0f, *link_to_player->position_y + 10.0f, EColor::COLOR_RED, EColor::COLOR_DARK_RED);
		}

		//EFont::active_font->draw_with_background("target vector x:" + std::to_string(*link_to_player->target_vector_x), EGraphicCore::batch, *link_to_player->position_x + 100.0f, *link_to_player->position_y - 10.0f, EColor::COLOR_LIGHT_GRAY, EColor::COLOR_DARK_GRAY);
		//EFont::active_font->draw_with_background("target vector y:" + std::to_string(*link_to_player->target_vector_y), EGraphicCore::batch, *link_to_player->position_x + 100.0f, *link_to_player->position_y - 30.0f, EColor::COLOR_LIGHT_GRAY, EColor::COLOR_DARK_GRAY);
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

	/*
	EGraphicCore::batch->setcolor(EColor::COLOR_DARK_GRAY);
	EGraphicCore::batch->draw_gabarite(250.0f, 5.0f, 200.0f, 20.0f, EGraphicCore::gabarite_white_pixel);
	EGraphicCore::batch->setcolor(EColor::COLOR_LIGHT_GRAY);
	EFont::active_font->draw(EGraphicCore::batch, std::to_string(round(*link_to_player->speed_x * 0.04f * 3.6f) ), 257.0f, 7.0f);

	EGraphicCore::batch->setcolor(EColor::COLOR_DARK_GRAY);
	EGraphicCore::batch->draw_gabarite(450.0f, 5.0f, 200.0f, 20.0f, EGraphicCore::gabarite_white_pixel);
	EGraphicCore::batch->setcolor(EColor::COLOR_LIGHT_GRAY);
	EFont::active_font->draw(EGraphicCore::batch, std::to_string(round(*link_to_player->speed_y * 0.04 * 3.6f)), 457.0f, 7.0f);*/

	/*
	if (selected_entity)
	EGraphicCore::batch->setcolor(EColor::COLOR_DARK_GRAY);
	EGraphicCore::batch->draw_gabarite(450.0f, 5.0f, 200.0f, 20.0f, EGraphicCore::gabarite_white_pixel);
	EGraphicCore::batch->setcolor(EColor::COLOR_LIGHT_GRAY);
	EFont::active_font->draw(EGraphicCore::batch, std::to_string(round(*link_to_player->speed_y * 0.04 * 3.6f)), 457.0f, 7.0f);*/

	if (time_process_active)
	{
		float time_process_h = 0.0f;
		float time_process_summ = 0.0f;

		float offset_y = 0.0f;

		
		for (time_process_struct* str:tps_list)
		{
			//time_process_summ += str->time_process_value.at(time_process_rota_id);


			//EFont::active_font->draw(EGraphicCore::batch, EString::float_to_string(round(str->time_process_value.at(time_process_rota_id) * 100.0f) / 100.0f), 205.0f, EGraphicCore::SCR_HEIGHT - 52.0f - offset_y + 3.0f);
		
			float time_process_average = 0.0f;
			float min_value = 100.0f;
			float max_value = 0.0f;
			for (int i = 0; i < 30; i++)
			{
				float current = str->time_process_value.at(i);
				time_process_average += current;

				if (current < min_value) { min_value = current; }
				if (current > max_value) { max_value = current; }
			}

			time_process_average /= 30.0f;
			time_process_summ += time_process_average;

			if (glfwGetKey(EWindow::main_window, GLFW_KEY_TAB) == GLFW_PRESS)
			{
				EGraphicCore::batch->setcolor_alpha(EColor::COLOR_BLACK, 0.9f);
				EGraphicCore::batch->draw_gabarite(0.0f, EGraphicCore::SCR_HEIGHT - 52.0f - offset_y, 300.0f, 20.0f, EGraphicCore::gabarite_white_pixel);

				EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 0.9f);
				EFont::active_font->draw(EGraphicCore::batch, str->time_process_name, 5.0f, EGraphicCore::SCR_HEIGHT - 52.0f - offset_y + 3.0f);

				EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 0.9f);
				EFont::active_font->draw(EGraphicCore::batch, EString::float_to_string(round(time_process_average * 100.0f) / 100.0f), 205.0f, EGraphicCore::SCR_HEIGHT - 52.0f - offset_y + 3.0f);

				EGraphicCore::batch->setcolor_alpha(EColor::COLOR_DARK_GREEN, 0.9f);
				EFont::active_font->draw(EGraphicCore::batch, EString::float_to_string(min_value), 255.0f, EGraphicCore::SCR_HEIGHT - 52.0f - offset_y + 3.0f);

				EGraphicCore::batch->setcolor_alpha(EColor::COLOR_DARK_RED, 0.9f);
				EFont::active_font->draw(EGraphicCore::batch, EString::float_to_string(max_value), 305.0f, EGraphicCore::SCR_HEIGHT - 52.0f - offset_y + 3.0f);
			}
			offset_y += 25.0f;
		}

		EGraphicCore::batch->setcolor_alpha(EColor::COLOR_BLACK, 0.9f);
		EGraphicCore::batch->draw_gabarite(0.0f, EGraphicCore::SCR_HEIGHT - 62.0f, 300.0f, 20.0f, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor_alpha(EColor::COLOR_PINK, 0.9f);
		EFont::active_font->draw(EGraphicCore::batch, "summ", 5.0f, EGraphicCore::SCR_HEIGHT - 62.0f + 3.0f);
		EFont::active_font->draw(EGraphicCore::batch, std::to_string(time_process_summ), 205.0f, EGraphicCore::SCR_HEIGHT - 62.0f + 3.0f);

		time_process_rota_id++;

		if (time_process_rota_id >= 30)
		{time_process_rota_id = 0;}
	}

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		EGraphicCore::batch->reinit();
		EGraphicCore::batch->draw_call();
		EGraphicCore::batch->reset();
		
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);

		glBindTexture(GL_TEXTURE_2D, EWindow::base_blockmap->colorbuffer);
		EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 1.0f);
		EGraphicCore::batch->draw_rect(0.0f, 000.0f, EWindow::base_blockmap->size_x, EWindow::base_blockmap->size_y);

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
