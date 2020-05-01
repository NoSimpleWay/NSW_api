#pragma once
#include "EWindowTest.h"
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
	for (int i = 0; i < 30; i++)
	{
		Entity* en = new Entity();

		//Entity::entity_list.push_back(en);
		*en->position_x = (float) (rand() % 1000) + ECluster::CLUSTER_SIZE * ECluster::CLUSTER_DIM /2.0f;
		*en->position_y = (float)(rand() % 1000) + ECluster::CLUSTER_SIZE * ECluster::CLUSTER_DIM / 2.0f;

		ECluster::put_entity(en, *en->position_x, *en->position_y);
	}

	link_to_player = new Entity();

	*link_to_player->position_x = +ECluster::CLUSTER_SIZE * ECluster::CLUSTER_DIM / 2.0f;
	*link_to_player->position_y = +ECluster::CLUSTER_SIZE * ECluster::CLUSTER_DIM / 2.0f;
	*link_to_player->mass = 100.0f;

	link_to_player->body.clear();
	link_to_player->body.push_back(ETextureAtlas::put_texture_to_atlas("data/mech_1.png", EWindow::default_texture_atlas));
	link_to_player->body.push_back(ETextureAtlas::put_texture_to_atlas("data/mech_2.png", EWindow::default_texture_atlas));
	link_to_player->body.push_back(ETextureAtlas::put_texture_to_atlas("data/mech_3.png", EWindow::default_texture_atlas));
	link_to_player->body.push_back(ETextureAtlas::put_texture_to_atlas("data/mech_4.png", EWindow::default_texture_atlas));

	link_to_player->body_rotate_by_move = true;

	link_to_player->body_offset_x.clear();
	link_to_player->body_offset_x.push_back(-27.0f);
	link_to_player->body_offset_x.push_back(-14.0f);
	link_to_player->body_offset_x.push_back(-27.0f);
	link_to_player->body_offset_x.push_back(-14.0f);

	link_to_player->body_offset_y.clear();
	link_to_player->body_offset_y.push_back(0.0f);
	link_to_player->body_offset_y.push_back(-5.0f);
	link_to_player->body_offset_y.push_back(0.0f);
	link_to_player->body_offset_y.push_back(-5.0f);

	ECluster::put_entity(link_to_player, *link_to_player->position_x, *link_to_player->position_y);

	link_to_player->controlled_by_ai = false;
	link_to_player->controlled_by_player = true;

	always_fullscreen = true;
	short default_path = 250;

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

}
	



EWindowTest::~EWindowTest()
{
}

void EWindowTest::default_update(float _d)
{
}

void EWindowTest::update(float _d)
{
	add_time_process("game_window_update");

	game_camera->position_x = *link_to_player->position_x;
	game_camera->position_y = *link_to_player->position_y;


	if (glfwGetKey(EWindow::main_window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		_d *= 0.00f;
	}

	if (LMB)
	{
		EPath::block
		[EMath::clamp_value_int((int)((EWindow::mouse_x + game_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f) / EPath::PATH_SIZE), 0, EPath::PATH_DIM - 1)]
		[EMath::clamp_value_int((int)((EWindow::mouse_y + game_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f) / EPath::PATH_SIZE), 0, EPath::PATH_DIM - 1)]
		= true;


		
		//EPath::block[0][0] = 1000;
	}

	if (RMB)
	{
		EPath::block
			[EMath::clamp_value_int((int)((EWindow::mouse_x + game_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f) / EPath::PATH_SIZE), 0, EPath::PATH_DIM - 1)]
		[EMath::clamp_value_int((int)((EWindow::mouse_y + game_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f) / EPath::PATH_SIZE), 0, EPath::PATH_DIM - 1)]
		= false;

		//EPath::block[0][0] = 1000;
	}

	

	int draw_border_left =	(int)((game_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f) / ECluster::CLUSTER_SIZE) - 1; if (draw_border_left < 0) { draw_border_left = 0; }
	int draw_border_right = (int)((game_camera->position_x + EGraphicCore::SCR_WIDTH / 2.0f) / ECluster::CLUSTER_SIZE) + 1; if (draw_border_right >= ECluster::CLUSTER_DIM) { draw_border_right = ECluster::CLUSTER_DIM - 1;; }

	int draw_border_down =	(int)((game_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f) / ECluster::CLUSTER_SIZE) - 1; if (draw_border_down < 0) { draw_border_down = 0; }
	int draw_border_up =	(int)((game_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f) / ECluster::CLUSTER_SIZE) + 1; if (draw_border_up > ECluster::CLUSTER_DIM) { draw_border_up = ECluster::CLUSTER_DIM - 1; }


	//----------------PATH MATRIX GABARITES----------------
	int left_path_draw = (int)((game_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f) / EPath::PATH_SIZE) - 3; if (left_path_draw < 0) { left_path_draw = 0; }
	int right_path_draw = (int)((game_camera->position_x + EGraphicCore::SCR_WIDTH / 2.0f) / EPath::PATH_SIZE) + 3; if (right_path_draw >= EPath::PATH_DIM) { right_path_draw = EPath::PATH_DIM - 1; }

	int down_path_draw = (int)((game_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f) / EPath::PATH_SIZE) - 3; if (down_path_draw < 0) { down_path_draw = 0; }
	int up_path_draw = (int)((game_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f) / EPath::PATH_SIZE) + 3; if (up_path_draw >= EPath::PATH_DIM) { up_path_draw = EPath::PATH_DIM - 1; }

	int left_path_heat_draw = left_path_draw - 1;		if (left_path_heat_draw < 0)					{ left_path_heat_draw = 0; }
	int right_path_heat_draw = right_path_draw + 1;		if (right_path_heat_draw >= EPath::PATH_DIM)	{ right_path_heat_draw = EPath::PATH_DIM - 1; }

	int up_path_heat_draw = up_path_draw + 1;			if (up_path_heat_draw >= EPath::PATH_DIM)		{ up_path_heat_draw = EPath::PATH_DIM - 1; }
	int down_path_heat_draw = down_path_draw - 1;		if (down_path_heat_draw < 0)					{ down_path_heat_draw = 0; }
	add_time_process("game_window_pre_path");
	//----------------ENTITIES PATH FIND----------------
	for (int i = draw_border_up;	i >= draw_border_down;	i--)
	for (int j = draw_border_left;	j <= draw_border_right;	j++)
	for (Entity* e : ECluster::clusters[j][i]->entity_list)
	{
		//clear block
		EPath::entity_block[(int)(*e->position_x / EPath::PATH_SIZE)][(int)(*e->position_y / EPath::PATH_SIZE)] = true;
	}


	//if (!EPath::block[(int)((game_camera->position_x + EGraphicCore::SCR_WIDTH / 200.0f) / EPath::PATH_SIZE)][(int)((game_camera->position_y + EGraphicCore::SCR_HEIGHT / 200.0f) / EPath::PATH_SIZE)])
	//{
	//	EPath::path[(int)((game_camera->position_x + EGraphicCore::SCR_WIDTH / 200.0f) / EPath::PATH_SIZE)][(int)((game_camera->position_y + EGraphicCore::SCR_HEIGHT / 200.0f) / EPath::PATH_SIZE)][EPath::back_buffer] = 0;
	//}

	EPath::cooldown -= _d;

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
					EPath::path[j][i][EPath::back_buffer] += 8;
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
	add_time_process("path_spread_finish");

	for (int i = draw_border_up;	i >= draw_border_down;	i--)
	for (int j = draw_border_left;	j <= draw_border_right;	j++)
	for (Entity* e : ECluster::clusters[j][i]->entity_list)
	if (!*e->already_updated)
	{
		//clear block
		EPath::entity_block[(int)(*e->position_x / EPath::PATH_SIZE)][(int)(*e->position_y / EPath::PATH_SIZE)] = false;
	}

	for (int i = draw_border_up;	i >= draw_border_down;	i--)
	for (int j = draw_border_left;	j <= draw_border_right;	j++)
	for (Entity* e : ECluster::clusters[j][i]->entity_list)
	if (!*e->already_updated)
	{
		int dir_x = 0;
		int dir_y = 0;
		float dir_mul = 1.0f;

		int prev_cluster_x = (int)(*e->position_x / ECluster::CLUSTER_SIZE);
		int prev_cluster_y = (int)(*e->position_y / ECluster::CLUSTER_SIZE);

		if (e->controlled_by_player)
		{
			if (glfwGetKey(EWindow::main_window, GLFW_KEY_A) == GLFW_PRESS)
			{
				dir_x = -1;
			}

			if (glfwGetKey(EWindow::main_window, GLFW_KEY_D) == GLFW_PRESS)
			{
				dir_x = 1;
			}

			if (glfwGetKey(EWindow::main_window, GLFW_KEY_S) == GLFW_PRESS)
			{
				dir_y = -1;
			}

			if (glfwGetKey(EWindow::main_window, GLFW_KEY_W) == GLFW_PRESS)
			{
				dir_y = 1;
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

			bool up_block = EPath::block[path_pos_left][path_pos_up] || EPath::block[path_pos_right][path_pos_up];
			bool down_block = EPath::block[path_pos_left][path_pos_down] || EPath::block[path_pos_right][path_pos_down];


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

				/*
				if (left_dir < right_dir)
				{
					dir_x = -1;
				}
				else
				{
					dir_x = 1;
				}

				if (down_dir < up_dir)
				{
					dir_y = -1;
				}
				else
				{
					dir_y = 1;
				}*/
			}

			/*
			//block x-axis move if unwalking map near
			if ((EPath::block[path_pos_x + dir_x][path_pos_down] > 999) || (EPath::block[path_pos_x + dir_x][path_pos_up] > 999))
			{
				dir_x = 0;
			}

			//block y-axis move if unwalking map near
			if ((EPath::block[path_pos_left][path_pos_y + dir_y] > 999) || (EPath::block[path_pos_right][path_pos_y + dir_y] > 999))
			{
				dir_y = 0;
			}*/

			//anti corner move
			//if ((EPath::block[path_pos_left][path_pos_y + dir_y])||(EPath::block[path_pos_right][path_pos_y + dir_y]))
			//{
			//	dir_y = 0;
			//}
			//if (left_block)
			//{
			//	dir_x = 1;
			//}


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

			if (dir_x * dir_y != 0)
			{
				dir_mul = 0.7f;
			}
		}

		//add_time_process("entities_path_find");

		*e->speed_x += dir_x * _d * 500.0f * dir_mul;
		*e->speed_y += dir_y * _d * 500.0f * dir_mul;

		*e->real_speed_x = *e->speed_x * _d;
		*e->real_speed_y = *e->speed_y * _d;

		bool collision_left = false;
		bool collision_right = false;
		bool collision_up = false;
		bool collision_down = false;

		float total_impulse = 0;
		float total_mass = 0;
		float transfer_multiplier = 0;
		float speed_diff = 0;

		float delta = 0;

		////
		////===>
		////
		for (int k = 0; k <= 1; k++)
		for (int z = -1; z <= 1; z++)
		for (Entity* e2 : ECluster::clusters[j + k][i + z]->entity_list)
		if (e!=e2)
		{
			if (ECluster::collision_left(e, e2))
			{
				collision_left = true;



				if ((*e->speed_x) > (*e2->speed_x))
				{
					total_mass = *e->mass + *e2->mass;
					total_impulse = (*e->mass * *e->speed_x) + (*e2->mass * *e2->speed_x);

					*e->speed_x = total_impulse / total_mass;
					*e2->speed_x = total_impulse / total_mass;
					//*e->position_x -= 1.0f;
				}
			}


		}

		for (int k = 0; k >= -1; k--)
		for (int z = -1; z <= 1; z++)
		for (Entity* e2 : ECluster::clusters[j + k][i + z]->entity_list)
		if (e!=e2)
		{
		if (ECluster::collision_right(e, e2))
		{
			collision_right = true;

			if ((*e->speed_x) < (*e2->speed_x))
			{
				total_mass = *e->mass + *e2->mass;
				total_impulse = (*e->mass * *e->speed_x) + (*e2->mass * *e2->speed_x);

				*e->speed_x = total_impulse / total_mass;
				*e2->speed_x = total_impulse / total_mass;
				//*e->position_x -= 1.0f;
			}
		}
		}

		for (int k = 0; k >= -1; k--)
		for (int z = -1; z <= 1; z++)
			for (Entity* e2 : ECluster::clusters[j + z][i + k]->entity_list)
				if (e != e2)
				{
					if (ECluster::collision_up(e, e2))
					{
						collision_up = true;

						if ((*e->speed_y) < (*e2->speed_y))
						{
							total_mass = *e->mass + *e2->mass;
							total_impulse = (*e->mass * *e->speed_y) + (*e2->mass * *e2->speed_y);

							*e->speed_y = total_impulse / total_mass;
							*e2->speed_y = total_impulse / total_mass;
							//*e->position_x -= 1.0f;
						}
					}


				}

		for (int k = 0; k <= 1; k++)
		for (int z = -1; z <= 1; z++)
			for (Entity* e2 : ECluster::clusters[j + z][i + k]->entity_list)
				if (e != e2)
				{
					if (ECluster::collision_down(e, e2))
					{
						collision_down = true;

						if ((*e->speed_y) > (*e2->speed_y))
						{
							total_mass = *e->mass + *e2->mass;
							total_impulse = (*e->mass * *e->speed_y) + (*e2->mass * *e2->speed_y);

							*e->speed_y = total_impulse / total_mass;
							*e2->speed_y = total_impulse / total_mass;
							//*e->position_x -= 1.0f;
						}
					}


				}

		//if (!any_collision)
		{
			if ((!collision_left)&&(!collision_right))
			{
				*e->position_x += *e->speed_x * _d;
			}
			
			if ((!collision_up) && (!collision_down))
			{
				*e->position_y += *e->speed_y * _d;
			}
		}

		*e->speed_x *= pow(0.1, _d);
		*e->speed_y *= pow(0.1, _d);

	

		//EPath::block[(int)(*e->position_x / EPath::PATH_SIZE)][(int)(*e->position_y / EPath::PATH_SIZE)] -= EPath::ENTITY_BLOCK_VALUE;

		int new_cluster_x = (int)(*e->position_x / ECluster::CLUSTER_SIZE);
		int new_cluster_y = (int)(*e->position_y / ECluster::CLUSTER_SIZE);

		
		if ((new_cluster_x != prev_cluster_x) || (new_cluster_y != prev_cluster_y))
		{
			*e->need_change_cluster = true;
		}

		*e->already_updated = true;
	}

	add_time_process("entities_update");

	for (int i = draw_border_up;	i >= draw_border_down;	i--)
	for (int j = draw_border_left;	j <= draw_border_right;	j++)
	{
		for (int k = 0; k < ECluster::clusters[j][i]->entity_list.size(); k++)
		{
			Entity* e = ECluster::clusters[j][i]->entity_list.at(k);

			*e->already_updated = false;

			if (*e->need_change_cluster)
			{
				ECluster::clusters[j][i]->entity_list.erase(ECluster::clusters[j][i]->entity_list.begin() + k);
				ECluster::put_entity(e, *e->position_x, *e->position_y);

				*e->need_change_cluster = false;

				k++;
			}
		}
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


	//for (int i = EPath::clamp_phase; i < EPath::PATH_DIM; i++)



	//----------------DRAW PATH MATRIX----------------
	if (true)
	for (int i = up_path_draw; i >= down_path_draw; i--)
	for (int j = left_path_draw; j <= right_path_draw; j++)
	{
		if (EPath::block[j][i])
		{
			EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		}
		else
		{
			EGraphicCore::batch->setcolor_lum(EColor::COLOR_WHITE, 1.0f - EMath::clamp_value_float(EPath::path[j][i][EPath::active_buffer] / 100.0f, 0.0f, 1.0f));

			if (EPath::path[j][i][EPath::active_buffer] < 5)
			{
				EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
			}
		}



		EGraphicCore::batch->draw_gabarite(j * EPath::PATH_SIZE, i * EPath::PATH_SIZE, EPath::PATH_SIZE, EPath::PATH_SIZE, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor(EColor::COLOR_ORANGE);
		EFont::active_font->draw(EGraphicCore::batch, std::to_string(EPath::path[j][i][EPath::active_buffer]), j * EPath::PATH_SIZE + 20.0f, i * EPath::PATH_SIZE + 10.0f);
	}

	//----------------DRAW ENTITIES----------------
	int draw_border_left =	(int)((game_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f) / ECluster::CLUSTER_SIZE) - 1; if (draw_border_left < 0) { draw_border_left = 0; }
	int draw_border_right = (int)((game_camera->position_x + EGraphicCore::SCR_WIDTH / 2.0f) / ECluster::CLUSTER_SIZE) + 1; if (draw_border_right >= ECluster::CLUSTER_DIM) { draw_border_right = ECluster::CLUSTER_DIM - 1;; }

	int draw_border_down =	(int)((game_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f) / ECluster::CLUSTER_SIZE) - 1; if (draw_border_down < 0) { draw_border_down = 0; }
	int draw_border_up =	(int)((game_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f) / ECluster::CLUSTER_SIZE) + 1; if (draw_border_up > ECluster::CLUSTER_DIM) { draw_border_up = ECluster::CLUSTER_DIM - 1; }

	
	for (int i = draw_border_up;	i >= draw_border_down;	i--)
	for (int j = draw_border_left;	j <= draw_border_right;	j++)
	{
		EGraphicCore::batch->setcolor(EColor::COLOR_BLACK);
		EGraphicCore::batch->draw_rama(j * ECluster::CLUSTER_SIZE, i * ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, 2, EGraphicCore::gabarite_white_pixel);

		
		for (Entity* e : ECluster::clusters[j][i]->entity_list)
		{
			EGraphicCore::batch->setcolor(EColor::COLOR_BLUE);
			EGraphicCore::batch->draw_rama(*e->position_x - *e->collision_left, *e->position_y - *e->collision_down, *e->collision_left+*e->collision_right, *e->collision_down + *e->collision_up, 1.0f, EGraphicCore::gabarite_white_pixel);

			int sprite_id = 0;
			EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);

			
			if (e->body_rotate_by_move)
			{
				if (*e->speed_x * *e->speed_x > *e->speed_y * *e->speed_y)
				{
					if (*e->speed_x > 0) { sprite_id = 1; } else {sprite_id = 3;}
				}
				else
				{
					if (*e->speed_y > 0) { sprite_id = 0; } else {sprite_id = 2;}
				}
			}
			
			EGraphicCore::batch->draw_gabarite(*e->position_x + e->body_offset_x.at(sprite_id), *e->position_y + e->body_offset_y.at(sprite_id), e->body.at(sprite_id)->size_x, e->body.at(sprite_id)->size_y, e->body.at(sprite_id));


		}
	}

	
	/*EGraphicCore::batch->setcolor(EColor::COLOR_BLACK);
	EGraphicCore::batch->draw_gabarite(100.0f + rand() % 10, 200.0f, 512.0f, 64.0f, EGraphicCore::gabarite_white_pixel);*/
}

void EWindowTest::draw_interface(float _d)
{
	EGraphicCore::batch->reinit();
	EGraphicCore::batch->draw_call();


	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1, -1, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x, EGraphicCore::correction_y, 1));

	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	//סבנמס באעקונא
	EGraphicCore::batch->reset();


	EGraphicCore::batch->setcolor(EColor::COLOR_DARK_GRAY);
	EGraphicCore::batch->draw_gabarite(5.0f, 5.0f, 200.0f, 20.0f, EGraphicCore::gabarite_white_pixel);

	EGraphicCore::batch->setcolor(EColor::COLOR_LIGHT_GRAY);
	EFont::active_font->draw(EGraphicCore::batch, std::to_string(round(1.0f / _d)), 7.0f, 7.0f);

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
		EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 1.0f);
		EGraphicCore::batch->draw_rect(0.0f, 0.0f, EGraphicCore::SCR_WIDTH, EGraphicCore::SCR_HEIGHT);
	}
}
