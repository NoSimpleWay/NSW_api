#include "EBA.h"
#include <iostream>
#include "EntityManager.h"

#include "EWindowTest.h"
#include "EWindowEditor.h"
#include "EWindowSearchBrick.h"

#include <direct.h>

void (*foo)();

EBA::EBA()
{
}

EBA::~EBA()
{
}




void EBA::set_method(void(*function)())
{
	foo = function;

	foo();

	//function();
}

void EBA::do_something()
{
}

void EBA::action_add_new_sprite(EButton* _b, float _d)
{
	ESprite* spr = new ESprite();


	EWindow::window_editor->selected_entity->sprite_list.insert
	(
		EWindow::window_editor->selected_entity->sprite_list.begin() + EWindow::window_editor->selected_sprite_id + 1,
		spr
	);

	EWindow::window_editor->selected_sprite_id++;
	EWindow::window_editor->selected_frame_id = 0;


	EWindow::window_editor->update_sprite_buttons();
}

void EBA::action_select_sprite(EButton* _b, float _d)
{
	//SetCursorPos(0, 0);

	/*POINT cursorPos;
	GetCursorPos(&cursorPos);
	float x = 0;
	x = cursorPos.x;
	float y = 0;
	y = cursorPos.y;
	
	char msg[50];*/

//	sprintf(msg, "x: %.2f\n"
//		"y : %.2f\n", x, y);

	//MessageBox(0, msg, "Mouse Position", 0);

	//std::cout << "x=" << x << "y=" << y << endl;

	//EWindow::push_cursor(-20.0f, 0.0f);

	EWindow::window_editor->selected_frame_id = 0;
	EWindow::window_editor->selected_sprite_id = _b->data_id;
	EWindow::window_editor->selected_sprite_button = _b;

	


	//EWindow::window_search_brick->is_active = true;

	EWindow::window_editor->update_sprite_buttons();
}

void EBA::action_set_sprite_texture(EButton* _b, float _d)
{
	EWindow::window_editor->selected_entity->sprite_list.at(EWindow::window_editor->selected_sprite_id)->gabarite.at(EWindow::window_editor->selected_frame_id) = _b->gabarite;

	EWindow::window_editor->update_sprite_buttons();

	EWindow::window_search_brick->is_active = false;
}

void EBA::action_open_select_texture_window(EButton* _b, float _d)
{
	EWindow::window_search_brick->is_active = true;
	EWindow::window_search_brick->search_mode = EWindowSearchBrick::SearchMode::SEARCH_TEXTURE;

	EWindow::window_search_brick->update_search(EWindow::window_search_brick->link_to_input);


	EWindow::window_editor->update_sprite_buttons();
}

void EBA::action_set_button_as_removed(EButton* _b, float _d)
{
	_b->need_remove = true;
}

void EBA::action_close_window(EButton* _b, float _d)
{
	_b->master_window->is_active = false;

	//_b->master_window->window_size_x *= 0.9f;
}


void EBA::save_to_file(std::string& w_string, Entity* e, int& order, bool _to_collection)
{
	w_string += "ADD_NEW_ENTITY";

	//just_created_entity = new Entity();

	w_string += "\t";
	w_string += std::to_string(*e->position_x);

	w_string += "\t";
	w_string += std::to_string(*e->position_y);

	w_string += "\n";

	for (ESprite* spr : e->sprite_list)
	{
		w_string += "ADD_NEW_SPRITE\n";

		if (*spr->rotate_by_move) { w_string += "*rotate_by_move\n"; }
		if (*spr->wall_mode) { w_string += "*wall_mode\n"; }

		order = 0;
		for (EGabarite* g : spr->gabarite)
		{
			w_string += "add_new_texture\t";
			w_string += g->name;
			w_string += "\n";

			w_string += "texture_offset_x\t";
			w_string += std::to_string(spr->offset_x.at(order));
			w_string += "\n";

			w_string += "texture_offset_y\t";
			w_string += std::to_string(spr->offset_y.at(order));
			w_string += "\n";

			w_string += "texture_copies\t";
			w_string += std::to_string(spr->copies.at(order));
			w_string += "\n";

			order++;
		}
	}

	if (e->controlled_by_player)
	{
		w_string += "*entity_controlled_by_player\n";
	}

	if (e->controlled_by_ai)
	{
		w_string += "*entity_controlled_by_ai\n";
	}

	if ((!_to_collection) & (EWindow::window_test->link_to_player == e))
	{
		w_string += "*camera_target\n";
	}

	if (*e->inmovable)
	{
		w_string += "*inmovable\n";
	}
	else
	{
		w_string += "mass\t";
		w_string += std::to_string(*e->mass);
		w_string += "\n";
	}

	w_string += "collision_up\t";
	w_string += std::to_string(*e->collision_up);
	w_string += "\n";

	w_string += "collision_down\t";
	w_string += std::to_string(*e->collision_down);
	w_string += "\n";

	w_string += "collision_right\t";
	w_string += std::to_string(*e->collision_right);
	w_string += "\n";

	w_string += "collision_left\t";
	w_string += std::to_string(*e->collision_left);
	w_string += "\n";

	if (e->action_on_hit != NULL)
	{
		w_string += "hit_action\t";

		std::string name_of_action = Entity::get_hit_action_name(e->action_on_hit);

		if (name_of_action != "")
		{
			w_string += name_of_action;
		}

		w_string += "\n";
	}

	if (_to_collection)
	{w_string += "- PUT TO COLLECTION -\n\n";}
	else
	{w_string += "- PUT TO MAP -\n\n";}

	w_string += "=====================================\n\n";
}

void EBA::action_save_map(EButton* _b, float _d)
{
	//Entity* just_created_entity = NULL;
	std::cout << "save" << std::endl;

	std::string zzz = "test";
	_mkdir(zzz.c_str());

	std::string w_string = "";
	int order = 0;

	ofstream writer;
	writer.open("test/map.txt");

		for (int j=0; j<ECluster::CLUSTER_DIM; j++)
		for (int i = 0; i < ECluster::CLUSTER_DIM; i++)
		for (Entity* e : ECluster::clusters[j][i]->entity_list)
		{
			EBA::save_to_file(w_string, e, order, false);
		}

	writer << w_string;
	writer.close();
}

void EBA::action_save_entity_to_collection(EButton* _b, float _d)
{
	Entity::entity_collection_list.push_back(EWindow::window_editor->selected_entity);
	//Entity* just_created_entity = NULL;
	std::cout << "save" << std::endl;

	std::string zzz = "test";
	_mkdir(zzz.c_str());

	std::string w_string = "";
	int order = 0;

	ofstream writer;
	writer.open("test/entity_collection.txt");

	for (Entity* e:Entity::entity_collection_list)
	{
		EBA::save_to_file(w_string, e, order, true);
	}

	writer << w_string;
	writer.close();
}


void EBA::read_data_for_entity(std::ifstream& myfile)
{
	{
		std::string line;
		Entity* just_created_entity = NULL;
		ESprite* just_created_sprite = NULL;
		EGabarite* just_created_gabarite = NULL;
		while (getline(myfile, line))
		{

			//std::cout << "line |" << line << "|" << std::endl;
			EFile::data_parser(line);

			int data_order = 0;

			auto array_length = end(*EFile::data_array) - begin(*EFile::data_array);

			//std::cout << "array length:" << array_length << std::endl;
			for (int i = 0; i < EFile::array_size; i++)
			{
				std::cout << "=" << EFile::data_array[i] << "=" << std::endl;

				if (EFile::data_array[i] == "ADD_NEW_ENTITY")
				{
					just_created_entity = new Entity();
					i++; *just_created_entity->position_x = std::stof(EFile::data_array[i]);
					i++; *just_created_entity->position_y = std::stof(EFile::data_array[i]);


				}

				if ((EFile::data_array[i] == "*entity_controlled_by_player") && (just_created_entity != NULL))
				{
					just_created_entity->controlled_by_player = true;
					//EWindow::window_test->link_to_player = just_created_entity;
					//EWindow::window_editor->selected_entity = just_created_entity;
				}

				if ((EFile::data_array[i] == "*inmovable") && (just_created_entity != NULL))
				{
					*just_created_entity->inmovable = true;
				}

				if ((EFile::data_array[i] == "*camera_target") && (just_created_entity != NULL))
				{
					EWindow::window_test->link_to_player = just_created_entity;
				}

				if (EFile::data_array[i] == "ADD_NEW_SPRITE")
				{
					just_created_sprite = new ESprite();

					ESprite::clear_default_data(just_created_sprite);
					just_created_entity->sprite_list.push_back(just_created_sprite);
				}

				if (EFile::data_array[i] == "add_new_texture")
				{
					i++; just_created_gabarite = ETextureAtlas::put_texture_to_atlas(EFile::data_array[i], EWindow::default_texture_atlas);
					just_created_sprite->gabarite.push_back(just_created_gabarite);
				}

				if (EFile::data_array[i] == "texture_offset_x")
				{
					i++; just_created_sprite->offset_x.push_back(std::stof(EFile::data_array[i]));
				}

				if (EFile::data_array[i] == "texture_offset_y")
				{
					i++; just_created_sprite->offset_y.push_back(std::stof(EFile::data_array[i]));
				}

				if (EFile::data_array[i] == "texture_copies")
				{
					i++; just_created_sprite->copies.push_back(std::stoi(EFile::data_array[i]));
				}

				if (EFile::data_array[i] == "*rotate_by_move") { *just_created_sprite->rotate_by_move = true; }
				if (EFile::data_array[i] == "*wall_mode") { *just_created_sprite->wall_mode = true; }

				if (EFile::data_array[i] == "mass")
				{
					i++; *just_created_entity->mass = std::stof(EFile::data_array[i]);

					std::cout << "mass is:" << std::to_string(*just_created_entity->mass) << std::endl;
				}


				if (EFile::data_array[i] == "collision_down") { i++; *just_created_entity->collision_down = std::stof(EFile::data_array[i]); }
				if (EFile::data_array[i] == "collision_left") { i++; *just_created_entity->collision_left = std::stof(EFile::data_array[i]); }
				if (EFile::data_array[i] == "collision_right") { i++; *just_created_entity->collision_right = std::stof(EFile::data_array[i]); }
				if (EFile::data_array[i] == "collision_up") { i++; *just_created_entity->collision_up = std::stof(EFile::data_array[i]); }

				if (EFile::data_array[i] == "hit_action")
				{
					i++;
					int hit_action_id = Entity::search_hit_action(EFile::data_array[i]);

					std::cout << "hit action is:" << hit_action_id << std::endl;

					if (hit_action_id != -1)
					{
						just_created_entity->action_on_hit = Entity::HIT_ACTIONS_LIST.at(hit_action_id);
					}
				}

				if (EFile::data_array[i] == "- PUT TO MAP -")
				{
					ECluster::put_entity(just_created_entity, *just_created_entity->position_x, *just_created_entity->position_y);
				}

				if (EFile::data_array[i] == "- PUT TO COLLECTION -")
				{
					Entity::entity_collection_list.push_back(just_created_entity);
				}
			}
		}
	}
}

void EBA::action_load_map(EButton* _b, float _d)
{
	ifstream myfile;

	if (_b != NULL)
	{myfile.open(_b->data_string);}
	else
	{myfile.open("test/map.txt");}


	for (int i = 0; i < ECluster::CLUSTER_DIM; i++)
	for (int j = 0; j < ECluster::CLUSTER_DIM; j++)
	{ECluster::clusters[j][i]->entity_list.clear();}

	read_data_for_entity(myfile);

	myfile.close();

	EWindow::window_editor->update_sprite_buttons();
}

void EBA::action_load_entity_collection(EButton* _b, float _d)
{	ifstream myfile;

	if (_b != NULL)
	{myfile.open(_b->data_string);}
	else
	{myfile.open("test/entity_collection.txt");}


	Entity::entity_collection_list.clear();

	read_data_for_entity(myfile);

	myfile.close();

	EWindow::window_editor->update_sprite_buttons();
}

void EBA::action_add_new_entity_from_collection(EButton* _b, float _d)
{
	/*Entity* en = new Entity();
	ESprite* spr = new ESprite();

	spr->gabarite.push_back(EGraphicCore::gabarite_white_pixel);

	spr->offset_x.push_back(0.0f);
	spr->offset_y.push_back(0.0f);

	en->sprite_list.push_back(spr);


	ECluster::put_entity(en, EWindow::window_test->game_camera->position_x, EWindow::window_test->game_camera->position_y);*/

	EWindow::window_editor->clone_entity(Entity::entity_collection_list.at(_b->data_id));
	EWindow::window_search_brick->is_active = false;
}

void EBA::action_add_new_entity(EButton* _b, float _d)
{
	Entity* en = new Entity();
	ESprite* spr = new ESprite();
	en->sprite_list.push_back(spr);

	ECluster::put_entity(en, EWindow::window_test->game_camera->position_x, EWindow::window_test->game_camera->position_y);

}

void EBA::action_open_select_entity_collection_window(EButton* _b, float _d)
{
	EWindow::window_search_brick->search_mode = EWindowSearchBrick::SearchMode::SEARCH_ENTITY;
	EWindow::window_search_brick->is_active = true;
	EWindow::window_search_brick->update_search(EWindow::window_search_brick->link_to_input);
}

void EBA::action_select_frame(EButton* _b, float _d)
{
	EWindow::window_editor->selected_frame_id = _b->data_id;


	EWindow::window_editor->update_sprite_buttons();
}

void EBA::action_move_sprite_up(EButton* _b, float _d)
{
	//std::cout << "data id = " << _b->data_id << std::endl;

	if (EWindow::window_editor->selected_sprite_id > 0)
	{
		ESprite* swap = EWindow::window_editor->selected_entity->sprite_list.at(EWindow::window_editor->selected_sprite_id - 1);

		EWindow::window_editor->selected_entity->sprite_list.at(EWindow::window_editor->selected_sprite_id - 1)
		=
		EWindow::window_editor->selected_entity->sprite_list.at(EWindow::window_editor->selected_sprite_id);

		EWindow::window_editor->selected_entity->sprite_list.at(EWindow::window_editor->selected_sprite_id) = swap;
	}

	EWindow::window_editor->update_sprite_buttons();
}

void EBA::action_move_sprite_down(EButton* _b, float _d)
{
	//std::cout << "size = " << std::to_string((EWindow::window_editor->sprite_button_list.size() + 10)) << std::endl;

	if
	(
		(EWindow::window_editor->selected_sprite_id + 1 < EWindow::window_editor->sprite_button_list.size())
		&&
		(EWindow::window_editor->selected_sprite_id + 1 < EWindow::window_editor->selected_entity->sprite_list.size())
	)
	{
		ESprite* swap = EWindow::window_editor->selected_entity->sprite_list.at(EWindow::window_editor->selected_sprite_id + 1);

		EWindow::window_editor->selected_entity->sprite_list.at(EWindow::window_editor->selected_sprite_id + 1)
		=
		EWindow::window_editor->selected_entity->sprite_list.at(EWindow::window_editor->selected_sprite_id);

		EWindow::window_editor->selected_entity->sprite_list.at(EWindow::window_editor->selected_sprite_id) = swap;
	}

	EWindow::window_editor->update_sprite_buttons();
}

void EBA::action_set_sprite_mode_4(EButton* _b, float _d)
{

	EWindowEditor* we = EWindow::window_editor;

	we->reset_mode(we->selected_entity->sprite_list.at(we->selected_sprite_id));

	*we->selected_entity->sprite_list.at(we->selected_sprite_id)->rotate_by_move = true;

	for (int i = we->selected_entity->sprite_list.at(we->selected_sprite_id)->gabarite.size(); i < 4; i++)
	{
		EGabarite* g = EGraphicCore::gabarite_white_pixel;

		we->selected_entity->sprite_list.at(we->selected_sprite_id)->offset_x.push_back(0);
		we->selected_entity->sprite_list.at(we->selected_sprite_id)->offset_y.push_back(0);

		we->selected_entity->sprite_list.at(we->selected_sprite_id)->gabarite.push_back(g);
		we->selected_entity->sprite_list.at(we->selected_sprite_id)->copies.push_back(1);
	}

	we->update_sprite_buttons();
}

void EBA::action_set_sprite_mode_wall(EButton* _b, float _d)
{
	EWindowEditor* we = EWindow::window_editor;
	we->reset_mode(we->selected_entity->sprite_list.at(we->selected_sprite_id));

	*we->selected_entity->sprite_list.at(we->selected_sprite_id)->wall_mode = !*we->selected_entity->sprite_list.at(we->selected_sprite_id)->wall_mode;
	EWindow::window_editor->update_sprite_buttons();
}

void EBA::action_set_mass(EButton* _b, float _d)
{
	if (EWindow::window_editor->selected_entity != NULL)
	{
		std::cout << "mass is:" << EMath::to_float(_b->text) << std::endl;
		//EWindow::window_editor->selected_entity;
	}
}

void EBA::action_set_inmovable(EButton* _b, float _d)
{
	if (EWindow::window_editor->selected_entity != NULL)
	{
		*EWindow::window_editor->selected_entity->inmovable = !*EWindow::window_editor->selected_entity->inmovable;
		EWindow::window_editor->selected_or_unselected_color(_b, EWindow::window_editor->selected_entity->inmovable);
	}
}

void EBA::action_set_controlled_by_player(EButton* _b, float _d)
{
	if (EWindow::window_editor->selected_entity != NULL)
	{
		EWindow::window_editor->selected_entity->controlled_by_player = !EWindow::window_editor->selected_entity->controlled_by_player;
		EWindow::window_editor->selected_or_unselected_color(_b, EWindow::window_editor->selected_entity->controlled_by_player);
	}
}

void EBA::action_set_controlled_by_AI(EButton* _b, float _d)
{
	if (EWindow::window_editor->selected_entity != NULL)
	{
		EWindow::window_editor->selected_entity->controlled_by_ai = !EWindow::window_editor->selected_entity->controlled_by_ai;
		EWindow::window_editor->selected_or_unselected_color(_b, EWindow::window_editor->selected_entity->controlled_by_ai);
	}
}

void EBA::action_set_camera_target(EButton* _b, float _d)
{
	if (EWindow::window_editor->selected_entity != NULL)
	{
		EWindow::window_test->link_to_player = EWindow::window_editor->selected_entity;
	}
}



/*
int EBA::search_hit_action(std::string _text)
{
	for (int i = 0; i < HIT_ACTION_NAME_LIST.size(); i++)
	{
		if (HIT_ACTION_NAME_LIST.at(i) == _text)
		{
			return i;
		}
	}
	return -1;
}
*/

void EBA::action_input_search_brick(EButton* _b, float _d)
{
	EWindow::window_search_brick->update_search(_b);
}


/*
void EBA::action_hit(Entity* _a, Entity* _b)
{
}*/

/*
void EBA::action_add_new_sprite()
{
}
*/
