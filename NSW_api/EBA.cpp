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

	spr->gabarite.push_back(ETextureAtlas::put_texture_to_atlas("data/textures/white_pixel.png", EWindow::default_texture_atlas));
	spr->offset_x.push_back(0.0f);
	spr->offset_y.push_back(0.0f);

	EWindow::window_editor->selected_entity->sprite_list.insert
	(
		EWindow::window_editor->selected_entity->sprite_list.begin() + EWindow::window_editor->selected_sprite_id,
		spr
	);
}

void EBA::action_select_sprite(EButton* _b, float _d)
{
	EWindow::window_editor->sprite_button_list.at(EWindow::window_editor->selected_sprite_id)->rama_color->set_color(EColor::COLOR_BLACK);
	EWindow::window_editor->selected_sprite_id = _b->data_id;
	_b->rama_color->set_color(EColor::COLOR_ORANGE);

	EWindow::window_search_brick->is_active = true;
}

void EBA::action_set_sprite_texture(EButton* _b, float _d)
{
	EWindow::window_test->link_to_player->sprite_list.at(EWindow::window_editor->selected_sprite_id)->gabarite.at(0) = _b->gabarite;
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
			w_string += "ADD_NEW_ENTITY\r\n";

			//just_created_entity = new Entity();

			w_string += "\t";
			w_string += std::to_string(*e->position_x);

			w_string += "\t";
			w_string += std::to_string(*e->position_y);

			w_string += "\r\n";

			for (ESprite* spr : e->sprite_list)
			{
				w_string += "ADD_NEW_SPRITE\r\n";

				if (spr->rotate_by_move)
				{
					w_string += "*rotate_by_move\r\n";
				}

				order = 0;
				for (EGabarite* g : spr->gabarite)
				{
					w_string += "add_new_texture\t";
					w_string += g->name;
					w_string += "\r\n";

					w_string += "texture_offset_x\t";
					w_string += std::to_string(spr->offset_x.at(order));
					w_string += "\r\n";

					w_string += "texture_offset_y\t";
					w_string += std::to_string(spr->offset_y.at(order));
					w_string += "\r\n";

					order++;
				}
			}

			if (e->controlled_by_player)
			{
				w_string += "*entity_controlled_by_player\r\n";
			}
			
			if (e->controlled_by_ai)
			{
				w_string += "*entity_controlled_by_ai\r\n";
			}
		}

	writer << w_string;
	writer.close();
}

void EBA::action_load_map(EButton* _b, float _d)
{
	ifstream myfile;
	myfile.open("test/map.txt");

	Entity* just_created_entity = NULL;
	ESprite* just_created_sprite = NULL;
	EGabarite* just_created_gabarite = NULL;



	std::string line;
	//cout << "open: " << _path << endl;

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

				ECluster::put_entity(just_created_entity, *just_created_entity->position_x, *just_created_entity->position_y);
			}
			
			if ((EFile::data_array[i] == "*entity_controlled_by_player") && (just_created_entity != NULL))
			{
				just_created_entity->controlled_by_player = true;
				EWindow::window_test->link_to_player = just_created_entity;
			}

			if (EFile::data_array[i] == "ADD_NEW_SPRITE")
			{
				just_created_sprite = new ESprite();
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
			
			if (EFile::data_array[i] == "*rotate_by_move")
			{
				*just_created_sprite->rotate_by_move = true;
			}


		}
	}

	myfile.close();
	//string line;
}



void EBA::action_input_search_brick(EButton* _b, float _d)
{
	EWindow::window_search_brick->update_search(_b);
}

/*
void EBA::action_add_new_sprite()
{
}
*/
