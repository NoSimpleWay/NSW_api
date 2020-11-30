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
	/*
	EWindow::window_editor->selected_entity->sprite_list.at(EWindow::window_editor->selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->gabarite = _b->gabarite;

	EWindow::window_editor->update_sprite_buttons();

	EWindow::window_search_brick->is_active = false;*/
	EWindowEditor* ed = EWindow::window_editor;

	//_b->gabarite = EWindow::window_editor->selected_entity->autobuilding_floor_list.at(ed->autobuilding_selected_floor)->wall_list.at(ed->autobuilding_selected_wall)->texture_variant_list.at(ed->selected_building_autogenerator_texture_variant)->texture;
	
		ed->selected_entity->autobuilding_floor_list.at(ed->autobuilding_selected_floor)->
	wall_list.at(ed->autobuilding_selected_wall)->
	texture_variant_list.at(ed->autobuilding_selected_texture_variant)->
	texture
	=
	_b->gabarite;

	ed->selected_entity->autobuilding_floor_list.at(ed->autobuilding_selected_floor)->
	wall_list.at(ed->autobuilding_selected_wall)->
	texture_variant_list.at(ed->autobuilding_selected_texture_variant)->
	supermap
	=
	ETextureAtlas::put_texture_to_atlas(_b->gabarite->name.substr(0, _b->gabarite->name.length() - 4) + "#supermap.png", EWindow::default_texture_atlas);;

	

	ed->link_to_texture_variant_array->button_list.at(ed->autobuilding_selected_texture_variant)->gabarite = _b->gabarite;

	EWindow::window_search_brick->is_active = false;

	ed->editor_mode = EWindowEditor::EditMode::EditAutobuilding;
	EWindow::window_editor->refresh_autobuilding();
}

void EBA::action_open_select_texture_window(EButton* _b, float _d)
{

	EWindow::window_search_brick->is_active = true;
	EWindow::window_search_brick->search_mode = EWindowSearchBrick::SearchMode::SEARCH_TEXTURE;

	EWindow::window_search_brick->update_search(EWindow::window_search_brick->link_to_input);



	/*EWindow::window_search_brick->is_active = true;
	EWindow::window_search_brick->search_mode = EWindowSearchBrick::SearchMode::SEARCH_TEXTURE;

	EWindow::window_search_brick->update_search(EWindow::window_search_brick->link_to_input);


	EWindow::window_editor->update_sprite_buttons();*/
}

void EBA::action_set_button_as_removed(EButton* _b, float _d)
{
	*_b->need_remove = true;
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
		if (*spr->is_shadow) { w_string += "*shadow\n"; }
		if (*spr->wall_mode) { w_string += "*wall_mode\n"; }
		if (*spr->rotate_by_target_gun) { w_string += "*target_gun\n"; }
		if (*spr->is_mirrored) { w_string += "*texture_mirrored\n";}


		order = 0;
		for (ESprite::sprite_struct* spr : spr->sprite_struct_list)
		{
			w_string += "add_new_texture\t";
			w_string += spr->gabarite->name;
			w_string += "\n";

			w_string += "texture_offset_x\t";
			w_string += std::to_string(*spr->offset_x);
			w_string += "\n";


			w_string += "texture_offset_y\t";
			w_string += std::to_string(*spr->offset_y);
			w_string += "\n";

			w_string += "texture_offset_z\t";
			w_string += std::to_string(*spr->offset_z);
			w_string += "\n";

			w_string += "texture_copies\t";
			w_string += std::to_string(*spr->copies);
			w_string += "\n";

			w_string += "shadow_size_x\t";
			w_string += std::to_string(*spr->shadow_size_x);
			w_string += "\n";

			w_string += "shadow_size_y\t";
			w_string += std::to_string(*spr->shadow_size_y);
			w_string += "\n";

			w_string += "shadow_tall\t";
			w_string += std::to_string(*spr->shadow_tall);
			w_string += "\n";

			w_string += "shadow_bottom_tall\t";
			w_string += std::to_string(*spr->bottom_tall);
			w_string += "\n";
			
			w_string += "fragment_x\t";
			w_string += std::to_string(*spr->fragment_x);
			w_string += "\n";
			
			w_string += "fragment_y\t";
			w_string += std::to_string(*spr->fragment_y);
			w_string += "\n";
		



			order++;
		}
	}

	for (Entity::building_autogen_floor* f : e->autobuilding_floor_list)
	{
		w_string += "add_new_autobuilding_floor\t";
			w_string += std::to_string(*f->offset_x) + "\t";
			w_string += std::to_string(*f->offset_y) + "\t";
			w_string += std::to_string(*f->offset_z) + "\t";
			w_string += std::to_string(*f->bottom_roof_offset_multiplier) + "\t";
			w_string += std::to_string(*f->up_roof_offset_multiplier) + "\t";
			w_string += std::to_string(*f->horizontal_roof_offset_multiplier);
		w_string += "\n";

		for (Entity::wall_element* w : f->wall_list)
		{
			w_string += "add_new_wall_for_floor\t";
				w_string += std::to_string(*w->offset_x) + "\t";
				w_string += std::to_string(*w->offset_y) + "\t";
				w_string += std::to_string(*w->offset_z) + "\t";
				w_string += std::to_string(*w->repeat_x) + "\t";
				w_string += std::to_string(*w->repeat_y);
			w_string += "\n";

			if (*w->is_mirrored)
			{ w_string += "*wall_is_mirrored\t"; }

			for (Entity::wall_texture_variant* t : w->texture_variant_list)
			if ((t != NULL)&&(t->texture != NULL))
			{
				w_string += "add_new_texture_variant_for_wall\t";
					w_string += t->texture->name + "\t";
					w_string += std::to_string(*t->offset_x) + "\t";
					w_string += std::to_string(*t->offset_y) + "\t";
					w_string += std::to_string(*t->offset_z) + "\t";

					w_string += std::to_string(*t->shadow_size_x) + "\t";
					w_string += std::to_string(*t->shadow_size_y) + "\t";
					w_string += std::to_string(*t->tall_bottom) + "\t";
					w_string += std::to_string(*t->tall_up);
				w_string += "\n";
			}
		}
	}


	/*if (e->controlled_by_player)
	{
		w_string += "*entity_controlled_by_player\n";
	}*/

	/*if (e->controlled_by_ai)
	{
		w_string += "*entity_controlled_by_ai\n";
	}*/

	if ((!_to_collection) & (EWindow::window_test->link_to_player == e))
	{
		w_string += "*camera_target\n";
	}

	/*if (*e->inmovable)
	{
		w_string += "*inmovable\n";
	}*/

	for (int i = 0; i <e->eattr_BASE.size(); i++)
	{
		int id = -1;

		for (int j = 0; j < Entity::entity_attribute_id.size(); j++)
		{
			if (Entity::entity_attribute_id.at(j) == i) { id = j; break; }
		}

		if ((id != -1) && (e->eattr_BASE.at(id) != 0.0f))
		{
			w_string += "entity base attribute\t";

			w_string += Entity::entity_attribute_names.at(id);
			w_string += "\t";
			w_string += std::to_string(e->eattr_BASE.at(id));

			w_string += "\n";
		}
	}

	for (int i = 0; i < e->pointer_to_bool_list.size(); i++)
	{
		int id = -1;

		for (int j = 0; j < Entity::entity_attribute_id.size(); j++)
		{
			if (Entity::entity_bool_attribute_id.at(j) == i) { id = j; break; }
		}

		if ((id != -1) && (*e->pointer_to_bool_list.at(id)))
		{
			w_string += "entity bool attribute\t";
			w_string += Entity::entity_bool_attribute_names.at(id);
			w_string += "\n";
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////

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

	////////////////////////////////////////////////////////////////////////////////////////////////

	w_string += "path_block_up\t";
	w_string += std::to_string(*e->path_block_gabarite_up);
	w_string += "\n";

	w_string += "path_block_down\t";
	w_string += std::to_string(*e->path_block_gabarite_down);
	w_string += "\n";

	w_string += "path_block_right\t";
	w_string += std::to_string(*e->path_block_gabarite_right);
	w_string += "\n";

	w_string += "path_block_left\t";
	w_string += std::to_string(*e->path_block_gabarite_left);
	w_string += "\n";

	////////////////////////////////////////////////////////////////////////////////////////////////


	w_string += "shadow_block_up\t";
	w_string += std::to_string(*e->shadow_block_gabarite_up);
	w_string += "\n";

	w_string += "shadow_block_down\t";
	w_string += std::to_string(*e->shadow_block_gabarite_down);
	w_string += "\n";

	w_string += "shadow_block_right\t";
	w_string += std::to_string(*e->shadow_block_gabarite_right);
	w_string += "\n";

	w_string += "shadow_block_left\t";
	w_string += std::to_string(*e->shadow_block_gabarite_left);
	w_string += "\n";

	////////////////////////////////////////////////////////////////////////////////////////////////

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

	if (EWindow::window_editor->selected_entity != NULL)
	{
		Entity::delete_unused_sprites(EWindow::window_editor->selected_entity);
	}
	//Entity* just_created_entity = NULL;
	std::cout << "save" << std::endl;

	std::string zzz = "test";
	_mkdir(zzz.c_str());

	std::string w_string = "";
	int order = 0;

	ofstream writer;
	writer.open("test/map.txt");

	w_string += "#shadow_skew\t";
	w_string += std::to_string(Batcher::skew_factor);
	w_string += "\n";

	w_string += "#lightmap_blur_factor\t";
	w_string += std::to_string(EWindowTest::blur_factor);
	w_string += "\n";

	w_string += "#lightmap_modes_blend\t";
	w_string += std::to_string(EWindowTest::blur_blend);
	w_string += "\n";

	w_string += "#blur_decay\t";
	w_string += std::to_string(EWindowTest::blur_decay_flat_factor);
	w_string += "\n";

		for (int j=0; j<ECluster::CLUSTER_DIM; j++)
		for (int i = 0; i < ECluster::CLUSTER_DIM; i++)
		for (Entity* e : ECluster::clusters[j][i]->entity_list)
		if(!*e->is_bullet)
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
		ESprite::sprite_struct* just_create_sprite_struct = NULL;

		Entity::building_autogen_floor* just_created_floor = NULL;
		Entity::wall_element* just_created_wall = NULL;
		Entity::wall_texture_variant* just_created_texture_variant = NULL;

		int wall_id = 0;


		while (getline(myfile, line))
		{

			//std::cout << "line |" << line << "|" << std::endl;
			EFile::data_parser(line);

			int data_order = 0;

			auto array_length = end(*EFile::data_array) - begin(*EFile::data_array);

			//std::cout << "array length:" << array_length << std::endl;
			for (int i = 0; i < EFile::array_size; i++)
			{
				//std::cout << "=" << EFile::data_array[i] << "=" << std::endl;

				if (EFile::data_array[i] == "#shadow_skew")
				{i++; Batcher::skew_factor = std::stof(EFile::data_array[i]);}

				if (EFile::data_array[i] == "#lightmap_blur_factor")
				{i++; EWindowTest::blur_factor = std::stof(EFile::data_array[i]);}

				if (EFile::data_array[i] == "#lightmap_modes_blend")
				{i++; EWindowTest::blur_blend = std::stof(EFile::data_array[i]);}

				if (EFile::data_array[i] == "#blur_decay")
				{i++; EWindowTest::blur_decay_flat_factor = std::stof(EFile::data_array[i]);}

				if (EFile::data_array[i] == "ADD_NEW_ENTITY")
				{
					wall_id = 0;
					just_created_entity = new Entity();
					i++; *just_created_entity->position_x = std::stof(EFile::data_array[i]);
					i++; *just_created_entity->position_y = std::stof(EFile::data_array[i]);
				}

				if ((EFile::data_array[i] == "*entity_controlled_by_player") && (just_created_entity != NULL))
				{
					*just_created_entity->controlled_by_player = true;
					//EWindow::window_test->link_to_player = just_created_entity;
					//EWindow::window_editor->selected_entity = just_created_entity;
				}

				if ((EFile::data_array[i] == "*entity_controlled_by_ai") && (just_created_entity != NULL))
				{
					*just_created_entity->controlled_by_ai = true;
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
					ESprite::clear_default_data(just_created_sprite);//set empty struct list

					//just_create_sprite_struct = just_created_sprite->sprite_struct_list.at(0);


					just_created_entity->sprite_list.push_back(just_created_sprite);
				}

				if (EFile::data_array[i] == "add_new_texture")
				{
					just_create_sprite_struct = new ESprite::sprite_struct;//create new struct
					just_created_sprite->sprite_struct_list.push_back(just_create_sprite_struct);//add struct to sprite

					i++;
					
					just_created_gabarite = ETextureAtlas::put_texture_to_atlas(EFile::data_array[i], EWindow::default_texture_atlas);
					just_create_sprite_struct->gabarite = just_created_gabarite;

					just_created_gabarite = ETextureAtlas::put_texture_to_atlas
					(
						EFile::data_array[i].substr(0, EFile::data_array[i].length() - 4) + "#supermap.png",
						EWindow::default_texture_atlas
					);

					just_create_sprite_struct->supermap = just_created_gabarite;
				}

				if (EFile::data_array[i] == "texture_offset_x")
				{
					i++; *just_create_sprite_struct->offset_x = std::stof(EFile::data_array[i]);
				}

				if (EFile::data_array[i] == "texture_offset_y")
				{
					i++; *just_create_sprite_struct->offset_y = std::stof(EFile::data_array[i]);
					//just_created_sprite->offset_z.push_back(0.0f);
				}

				if (EFile::data_array[i] == "texture_offset_z")
				{
					i++; *just_create_sprite_struct->offset_z = std::stof(EFile::data_array[i]);
				}

				if (EFile::data_array[i] == "shadow_size_x")
				{
					i++; *just_create_sprite_struct->shadow_size_x = std::stof(EFile::data_array[i]);
				}

				if (EFile::data_array[i] == "shadow_size_y")
				{
					i++; *just_create_sprite_struct->shadow_size_y = std::stof(EFile::data_array[i]);
				}

				if (EFile::data_array[i] == "shadow_tall")
				{
					i++; *just_create_sprite_struct->shadow_tall = std::stof(EFile::data_array[i]);
					//*just_create_sprite_struct->bottom_tall = std::stof(EFile::data_array[i]);
				}

				
				if (EFile::data_array[i] == "shadow_bottom_tall")
				{
					i++; *just_create_sprite_struct->bottom_tall = std::stof(EFile::data_array[i]);
				}

				if (EFile::data_array[i] == "fragment_x")
				{
					i++; *just_create_sprite_struct->fragment_x = std::stof(EFile::data_array[i]);
				}

				if (EFile::data_array[i] == "fragment_y")
				{
					i++; *just_create_sprite_struct->fragment_y = std::stof(EFile::data_array[i]);
				}

				if (EFile::data_array[i] == "texture_copies")
				{
					i++; *just_create_sprite_struct->copies = std::stoi(EFile::data_array[i]);
				}

				//Controlled by Player
				if (EFile::data_array[i] == "*texture_mirrored") { *just_created_sprite->is_mirrored = true; }
				if (EFile::data_array[i] == "*rotate_by_move") { *just_created_sprite->rotate_by_move = true; }
				if (EFile::data_array[i] == "*shadow") { *just_created_sprite->is_shadow = true; }
				if (EFile::data_array[i] == "*wall_mode") { *just_created_sprite->wall_mode = true; }
				if (EFile::data_array[i] == "*target_gun") { *just_created_sprite->rotate_by_target_gun = true; }
				
				if (EFile::data_array[i] == "entity base attribute")
				{
					i++;

					int id = -1;
					for (int j = 0; j < Entity::entity_attribute_names.size(); j++)
					{
						if (Entity::entity_attribute_names.at(j) == EFile::data_array[i]) { id = Entity::entity_attribute_id.at(j); break; }
					}

					if (id != -1)
					{i++;	just_created_entity->eattr_BASE.at(id) = std::stof(EFile::data_array[i]);}
				}

				if (EFile::data_array[i] == "entity bool attribute")
				{
					i++;

					int id = -1;
					for (int j = 0; j < Entity::entity_bool_attribute_names.size(); j++)
					{
						if (Entity::entity_bool_attribute_names.at(j) == EFile::data_array[i]) { id = Entity::entity_bool_attribute_id.at(j); break; }
					}

					if (id != -1)
					{
						*just_created_entity->pointer_to_bool_list.at(id) = true;
					}
				}
				/*
				if (EFile::data_array[i] == "mass")
				{
					i++; just_created_entity->eattr_BASE.at(Entity::EAttr::ENTITY_ATTRIBUTE_MASS) = std::stof(EFile::data_array[i]);

					//std::cout << "mass is:" << std::to_string(*just_created_entity->mass) << std::endl;
				}

				if (EFile::data_array[i] == "shadow_tall")
				{
					i++; *just_created_entity->shadow_tall_pointer = std::stof(EFile::data_array[i]);
				}
				*/

				if (EFile::data_array[i] == "collision_down") { i++; *just_created_entity->collision_down = std::stof(EFile::data_array[i]); }
				if (EFile::data_array[i] == "collision_left") { i++; *just_created_entity->collision_left = std::stof(EFile::data_array[i]); }
				if (EFile::data_array[i] == "collision_right") { i++; *just_created_entity->collision_right = std::stof(EFile::data_array[i]); }
				if (EFile::data_array[i] == "collision_up") { i++; *just_created_entity->collision_up = std::stof(EFile::data_array[i]); }

				if (EFile::data_array[i] == "path_block_down") { i++; *just_created_entity->path_block_gabarite_down = std::stof(EFile::data_array[i]); }
				if (EFile::data_array[i] == "path_block_left") { i++; *just_created_entity->path_block_gabarite_left = std::stof(EFile::data_array[i]); }
				if (EFile::data_array[i] == "path_block_right") { i++; *just_created_entity->path_block_gabarite_right = std::stof(EFile::data_array[i]); }
				if (EFile::data_array[i] == "path_block_up") { i++; *just_created_entity->path_block_gabarite_up = std::stof(EFile::data_array[i]); }

				if (EFile::data_array[i] == "shadow_block_down") { i++; *just_created_entity->shadow_block_gabarite_down = std::stof(EFile::data_array[i]); }
				if (EFile::data_array[i] == "shadow_block_left") { i++; *just_created_entity->shadow_block_gabarite_left = std::stof(EFile::data_array[i]); }
				if (EFile::data_array[i] == "shadow_block_right") { i++; *just_created_entity->shadow_block_gabarite_right = std::stof(EFile::data_array[i]); }
				if (EFile::data_array[i] == "shadow_block_up") { i++; *just_created_entity->shadow_block_gabarite_up = std::stof(EFile::data_array[i]); }

				if (EFile::data_array[i] == "hit_action")
				{
					i++;
					int hit_action_id = Entity::search_hit_action(EFile::data_array[i]);

					//std::cout << "hit action is:" << hit_action_id << std::endl;

					if (hit_action_id != -1)
					{
						just_created_entity->action_on_hit = Entity::HIT_ACTIONS_LIST.at(hit_action_id);
					}
				}

				if (EFile::data_array[i] == "- PUT TO MAP -")
				{
					Entity::update_entity_attributes(just_created_entity);

					ECluster::put_entity(just_created_entity, *just_created_entity->position_x, *just_created_entity->position_y);

				}

				if (EFile::data_array[i] == "- PUT TO COLLECTION -")
				{
					Entity::entity_collection_list.push_back(just_created_entity);
				}

				if (EFile::data_array[i] == "add_new_autobuilding_floor")
				{
					just_created_floor = new Entity::building_autogen_floor;
					just_created_entity->autobuilding_floor_list.push_back(just_created_floor);

					i++;  *just_created_floor->offset_x																= std::stof(EFile::data_array[i]);
					i++;  *just_created_floor->offset_y																= std::stof(EFile::data_array[i]);
					i++;  *just_created_floor->offset_z																= std::stof(EFile::data_array[i]);
					//i++;  std::cout << "|" << EFile::data_array[i] << "|" << std::endl; if (EFile::data_array[i] != "")*just_created_floor->bottom_roof_offset_multiplier = std::stof(EFile::data_array[i]);
					//i++;  std::cout << "|" << EFile::data_array[i] << "|" << std::endl; if (EFile::data_array[i] != "")  *just_created_floor->up_roof_offset_multiplier = std::stof(EFile::data_array[i]);
					//i++;  std::cout << "|" << EFile::data_array[i] << "|" << std::endl; if (EFile::data_array[i] != "")  *just_created_floor->horizontal_roof_offset_multiplier	= std::stof(EFile::data_array[i]);

					wall_id = 0;
				}
				
				if ((EFile::data_array[i] == "*wall_is_mirrored")&(just_created_wall != NULL))
				{*just_created_wall->is_mirrored = true;}

				if (EFile::data_array[i] == "add_new_wall_for_floor")
				{
					just_created_wall = just_created_floor->wall_list.at(wall_id);
					//just_created_floor->wall_list.at(wall_id);
					//just_created_floor->wall_list.push_back(just_created_wall);

					i++;  *just_created_wall->offset_x = std::stof(EFile::data_array[i]);
					i++;  *just_created_wall->offset_y = std::stof(EFile::data_array[i]);
					i++;  *just_created_wall->offset_z = std::stof(EFile::data_array[i]);
					i++;  *just_created_wall->repeat_x = std::stof(EFile::data_array[i]);
					i++;  *just_created_wall->repeat_y = std::stof(EFile::data_array[i]);

					wall_id++;
				}
				
				if (EFile::data_array[i] == "add_new_texture_variant_for_wall")
				{

					just_created_texture_variant = new Entity::wall_texture_variant;
					just_created_wall->texture_variant_list.push_back(just_created_texture_variant);

					i++;  just_created_texture_variant->texture = ETextureAtlas::put_texture_to_atlas(EFile::data_array[i], EWindow::default_texture_atlas);
					i++;  *just_created_texture_variant->offset_x = std::stof(EFile::data_array[i]);
					i++;  *just_created_texture_variant->offset_y = std::stof(EFile::data_array[i]);
					i++;  *just_created_texture_variant->offset_z = std::stof(EFile::data_array[i]);

					i++;  *just_created_texture_variant->shadow_size_x = std::stof(EFile::data_array[i]);
					i++;  *just_created_texture_variant->shadow_size_y = std::stof(EFile::data_array[i]);
					i++;  *just_created_texture_variant->tall_bottom = std::stof(EFile::data_array[i]);
					i++;  *just_created_texture_variant->tall_up = std::stof(EFile::data_array[i]);
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

	for (int i = 0; i < ECluster::CLUSTER_DIM; i++)
	for (int j = 0; j < ECluster::CLUSTER_DIM; j++)
	for (Entity* e:ECluster::clusters[j][i]->entity_list)
	{
		Entity::spread_path_block(e);
	}

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

	ECluster::put_entity(en, EWindow::window_test->game_camera->position_x / EWindow::window_test->game_camera->zoom, EWindow::window_test->game_camera->position_y / EWindow::window_test->game_camera->zoom);

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

		if (EWindow::window_editor->selected_sprite_id == EWindow::window_editor->selected_sprite_id)
		{EWindow::window_editor->selected_sprite_id--;}
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

		if (EWindow::window_editor->selected_sprite_id == EWindow::window_editor->selected_sprite_id)
		{EWindow::window_editor->selected_sprite_id++;}
	}

	EWindow::window_editor->update_sprite_buttons();
}

void EBA::action_set_sprite_mode_4(EButton* _b, float _d)
{

	EWindowEditor* we = EWindow::window_editor;

	we->reset_mode(we->selected_entity->sprite_list.at(we->selected_sprite_id));
	*we->selected_entity->sprite_list.at(we->selected_sprite_id)->rotate_by_move = true;

	for (int i = we->selected_entity->sprite_list.at(we->selected_sprite_id)->sprite_struct_list.size(); i < 4; i++)
	{

		ESprite::set_default_data(we->selected_entity->sprite_list.at(we->selected_sprite_id));
	}

	we->update_sprite_buttons();
}

void EBA::action_set_sprite_mode_8(EButton* _b, float _d)
{

	EWindowEditor* we = EWindow::window_editor;

	we->reset_mode(we->selected_entity->sprite_list.at(we->selected_sprite_id));

	*we->selected_entity->sprite_list.at(we->selected_sprite_id)->rotate_by_target_gun = true;

	for (int i = we->selected_entity->sprite_list.at(we->selected_sprite_id)->sprite_struct_list.size(); i < 8; i++)
	{
		EGabarite* g = EGraphicCore::gabarite_white_pixel;

		ESprite::set_default_data(we->selected_entity->sprite_list.at(we->selected_sprite_id));
	}

	we->update_sprite_buttons();
}

void EBA::action_slider_shadow_color(EButton* _b, float _d)
{
	if (_b->data_id == 0) { EColor::COLOR_LAZURE_SHADOW->color_red = _b->slider_value; }
	if (_b->data_id == 1) { EColor::COLOR_LAZURE_SHADOW->color_green = _b->slider_value; }
	if (_b->data_id == 2) { EColor::COLOR_LAZURE_SHADOW->color_blue = _b->slider_value; }
}

void EBA::action_slider_light_source_color(EButton* _b, float _d)
{
	if (EWindow::window_editor->selected_entity != NULL)
	{
		if (_b->data_id == 0) { EWindow::window_editor->selected_entity->eattr_BASE.at(Entity::EAttr::ENTITY_ATTRIBUTE_LIGHT_SOURCE_RED) = _b->slider_value; }
		if (_b->data_id == 1) { EWindow::window_editor->selected_entity->eattr_BASE.at(Entity::EAttr::ENTITY_ATTRIBUTE_LIGHT_SOURCE_GREEN) = _b->slider_value; }
		if (_b->data_id == 2) { EWindow::window_editor->selected_entity->eattr_BASE.at(Entity::EAttr::ENTITY_ATTRIBUTE_LIGHT_SOURCE_BLUE) = _b->slider_value; }

		Entity::update_entity_attributes(EWindow::window_editor->selected_entity);
	}
}

void EBA::action_slider_sky_color(EButton* _b, float _d)
{
	if (_b->data_id == 0) { EColor::COLOR_SKY_AMBIENT->color_red = _b->slider_value; }
	if (_b->data_id == 1) { EColor::COLOR_SKY_AMBIENT->color_green = _b->slider_value; }
	if (_b->data_id == 2) { EColor::COLOR_SKY_AMBIENT->color_blue = _b->slider_value; }
}

void EBA::action_select_entity_gabarite_mode(EButton* _b, float _d)
{
	*EWindow::window_editor->entity_gabarite_mode_active = _b->data_id;

	for (int i = 0; i < EWindow::window_editor->select_gabarite_mode_button_list.size(); i++)
	{
		EWindow::window_editor->select_gabarite_mode_button_list.at(i)->rama_thikness = 1.0f;
		EWindow::window_editor->select_gabarite_mode_button_list.at(i)->rama_color->set_color (EColor::COLOR_GRAY);
	}

	EWindow::window_editor->select_gabarite_mode_button_list.at(_b->data_id)->rama_thikness = 3.0f;
	EWindow::window_editor->select_gabarite_mode_button_list.at(_b->data_id)->rama_color->set_color(EColor::COLOR_YELLOW);
}

void EBA::action_set_sprite_mode_wall(EButton* _b, float _d)
{
	EWindowEditor* we = EWindow::window_editor;
	we->reset_mode(we->selected_entity->sprite_list.at(we->selected_sprite_id));

	for (int i = we->selected_entity->sprite_list.at(we->selected_sprite_id)->sprite_struct_list.size(); i < 3; i++)
	{

		ESprite::set_default_data(we->selected_entity->sprite_list.at(we->selected_sprite_id));
	}

	*we->selected_entity->sprite_list.at(we->selected_sprite_id)->wall_mode = !*we->selected_entity->sprite_list.at(we->selected_sprite_id)->wall_mode;
	EWindow::window_editor->update_sprite_buttons();
}

void EBA::action_set_shadow_mode(EButton* _b, float _d)
{
	EWindowEditor* we = EWindow::window_editor;

	*we->selected_entity->sprite_list.at(we->selected_sprite_id)->is_shadow = !*we->selected_entity->sprite_list.at(we->selected_sprite_id)->is_shadow;
	EWindow::window_editor->update_sprite_buttons();
}

void EBA::action_set_mass(EButton* _b, float _d)
{
	if (EWindow::window_editor->selected_entity != NULL)
	{
		std::cout << "mass is:" << EMath::to_float(_b->text) << std::endl;
		*EWindow::window_editor->selected_entity->mass_pointer = EMath::to_float(_b->text);
	}
}

void EBA::action_set_tall(EButton* _b, float _d)
{
	if (EWindow::window_editor->selected_entity != NULL)
	{
		std::cout << "tall is:" << EMath::to_float(_b->text) << std::endl;
		*EWindow::window_editor->selected_entity->shadow_tall_pointer = EMath::to_float(_b->text);
	}
}

void EBA::action_set_inmovable(EButton* _b, float _d)
{
	if (EWindow::window_editor->selected_entity != NULL)
	{
		*EWindow::window_editor->selected_entity->inmovable = !*EWindow::window_editor->selected_entity->inmovable;
		EWindow::window_editor->selected_or_unselected_color(_b, *EWindow::window_editor->selected_entity->inmovable);
	}
}

void EBA::action_set_controlled_by_player(EButton* _b, float _d)
{
	if (EWindow::window_editor->selected_entity != NULL)
	{
		*EWindow::window_editor->selected_entity->controlled_by_player = !*EWindow::window_editor->selected_entity->controlled_by_player;
		EWindow::window_editor->selected_or_unselected_color(_b, *EWindow::window_editor->selected_entity->controlled_by_player);
	}
}

void EBA::action_set_controlled_by_AI(EButton* _b, float _d)
{
	if (EWindow::window_editor->selected_entity != NULL)
	{
		*EWindow::window_editor->selected_entity->controlled_by_ai = !*EWindow::window_editor->selected_entity->controlled_by_ai;
		EWindow::window_editor->selected_or_unselected_color(_b, *EWindow::window_editor->selected_entity->controlled_by_ai);
	}
}

void EBA::action_set_camera_target(EButton* _b, float _d)
{
	if (EWindow::window_editor->selected_entity != NULL)
	{
		EWindow::window_test->link_to_player = EWindow::window_editor->selected_entity;
	}
}

void EBA::action_set_value_by_data_id(EButton* _b, float _d)
{
}

void EBA::action_set_entity_float_attribute(EButton* _b, float _d)
{
	if (EWindow::window_editor->selected_entity != NULL)
	{
		EWindow::window_editor->selected_entity->eattr_BASE.at(_b->data_id) = EMath::to_float(_b->text);

		Entity::update_entity_attributes(EWindow::window_editor->selected_entity);
	}
}

void EBA::action_set_entity_bool_attribute(EButton* _b, float _d)
{
	if (EWindow::window_editor->selected_entity != NULL)
	{
		*EWindow::window_editor->selected_entity->pointer_to_bool_list.at(_b->data_id) = !*EWindow::window_editor->selected_entity->pointer_to_bool_list.at(_b->data_id);

		EWindow::window_editor->selected_or_unselected_color(_b, *EWindow::window_editor->selected_entity->pointer_to_bool_list.at(_b->data_id));

		Entity::update_entity_attributes(EWindow::window_editor->selected_entity);
	}
}

void EBA::action_set_constant_int_to_address(EButton* _b, float _d)
{
	*_b->target_address_for_int = *_b->target_value_for_int;
}

void EBA::action_set_constant_bool_to_address(EButton* _b, float _d)
{
	*_b->target_address_for_bool = *_b->target_value_for_bool;
}

void EBA::action_set_button_value_bool_to_address(EButton* _b, float _d)
{
	if ((_b->target_address_for_bool != NULL) & (*_b->is_checkbox))
	{
		*_b->target_address_for_bool = *_b->is_checked;
	}
}

void EBA::action_set_button_value_float_to_address(EButton* _b, float _d)
{
	//logger("OWO");
	if (_b->have_input_mode)
	{
		*_b->target_address_for_float = EMath::to_float(_b->text);
	}

	if (((_b->is_slider)||(*_b->is_radial_button)) &(_b->target_address_for_float != NULL))
	{
		*_b->target_address_for_float = _b->slider_value;
	}
}

void EBA::action_add_new_texture_variant_button(EButton* _b, float _d)
{
	/*EButton* but = new EButton(0.0f, 0.0f, 100.0f, 100.0f);
	but->master_window = _b->master_window;
	but->can_be_removed = true;
	but->have_icon = true;

	EWindow::window_editor->link_to_texture_variant_array->button_list.push_back(but);*/
	/*
	EButton* but = EButton::clone_button(EWindow::window_editor->texture_variant_style_button, 0.0f, 0.0f, 100.0f, 100.0f);
	//EWindow::window_editor->texture_variant_style_button = but;

	but->bg_color->red = (rand() % 100) / 100.0f;
	but->bg_color->green = (rand() % 100) / 100.0f;
	but->bg_color->blue = (rand() % 100) / 100.0f;

	but->text = std::to_string(rand());

	EWindow::window_editor->link_to_texture_variant_array->button_list.push_back(but);*/

	for (EButton* b : EWindow::window_editor->link_to_texture_variant_array->button_list)
	{
		if (!b->is_active)
		{
			b->is_active = true;
			b->gabarite = NULL;

			break;
		}
	}

	if ((EWindow::window_editor->selected_entity != NULL) & (EWindow::window_editor->selected_entity->autobuilding_floor_list.size() > 0))
	{
		Entity::wall_texture_variant* tv = new Entity::wall_texture_variant;

		EWindow::window_editor->
		selected_entity->
		autobuilding_floor_list.at
		(EWindow::window_editor->autobuilding_selected_floor)->
		wall_list.at
		(EWindow::window_editor->autobuilding_selected_wall)->
		texture_variant_list.push_back(tv);

		if (EWindow::window_editor->autobuilding_selected_wall == Entity::WallElementIndex::WEI_SHADOW) { tv->texture = EGraphicCore::gabarite_white_pixel; }
	}
}

void EBA::action_select_building_autogenerator_wall_element(EButton* _b, float _d)
{
	EWindow::window_editor->move_mode = EWindowEditor::MoveMode::MoveWall;
	//int selected_id =
	EWindow::window_editor->autobuilding_selected_wall = _b->data_id;

	std::cout << "selected wall = " + std::to_string(EWindow::window_editor->autobuilding_selected_wall) << std::endl;

	//Entity::update_building_autogenerator_massive(EWindow::window_editor->selected_entity);

	//EWindow::window_editor->select_new_wall();
	EWindow::window_editor->refresh_autobuilding();

	//Entity::update_building_autogenerator_massive(EWindow::window_editor->selected_entity);


}

void EBA::action_deactivate_texture_variant(EButton* _b, float _d)
{
	_b->is_active = false;

		//EWindow::window_editor->select_new_variant();
	EWindow::window_editor->
	selected_entity->
	autobuilding_floor_list.at(EWindow::window_editor->autobuilding_selected_floor)->
	wall_list.at(EWindow::window_editor->autobuilding_selected_wall)->texture_variant_list.erase
	(
		EWindow::window_editor->
		selected_entity->
		autobuilding_floor_list.at(EWindow::window_editor->autobuilding_selected_floor)->
		wall_list.at(EWindow::window_editor->autobuilding_selected_wall)->texture_variant_list.begin()
		+
		EWindow::window_editor->autobuilding_selected_texture_variant
	);

	EWindow::window_editor->autobuilding_selected_texture_variant = 0;



	EButton* swap;

	for (int i = 0; i < EWindow::window_editor->link_to_texture_variant_array->button_list.size() - 1; i++)
	{
		EButton* button_a = EWindow::window_editor->link_to_texture_variant_array->button_list.at(i);
		EButton* button_b = EWindow::window_editor->link_to_texture_variant_array->button_list.at(i + 1);

		if
		(
			(!button_a->is_active)
			&
			(button_b->is_active)
		)
		{ 
			swap = button_a;
			EWindow::window_editor->link_to_texture_variant_array->button_list.at(i) = button_b;
			EWindow::window_editor->link_to_texture_variant_array->button_list.at(i + 1) = swap;
		}

	}

	for (int i = 0; i < EWindow::window_editor->link_to_texture_variant_array->button_list.size() - 1; i++)
	{
		EWindow::window_editor->link_to_texture_variant_array->button_list.at(i)->data_id = i;
	}

	EWindow::window_editor->count_of_variants--;



	EWindow::window_editor->refresh_autobuilding();
}

void EBA::action_deactivate_floors(EButton* _b, float _d)
{
	_b->is_active = false;

	EWindow::window_editor->selected_entity->autobuilding_floor_list.erase
	(
		EWindow::window_editor->selected_entity->autobuilding_floor_list.begin() + _b->data_id
	);

	if (EWindow::window_editor->autobuilding_selected_floor >= EWindow::window_editor->selected_entity->autobuilding_floor_list.size())
	{
		EWindow::window_editor->autobuilding_selected_floor = EWindow::window_editor->selected_entity->autobuilding_floor_list.size() - 1;
	}

	EButton* swap;

	for (int i = 0; i < EWindow::window_editor->link_to_floors_array->button_list.size() - 1; i++)
	{
		EButton* button_a = EWindow::window_editor->link_to_floors_array->button_list.at(i);
		EButton* button_b = EWindow::window_editor->link_to_floors_array->button_list.at(i + 1);

		if
			(
				(!button_a->is_active)
				&
				(button_b->is_active)
				)
		{
			swap = button_a;
			EWindow::window_editor->link_to_floors_array->button_list.at(i) = button_b;
			EWindow::window_editor->link_to_floors_array->button_list.at(i + 1) = swap;
		}

	}

	for (int i = 0; i < EWindow::window_editor->link_to_floors_array->button_list.size() - 1; i++)
	{
		EWindow::window_editor->link_to_floors_array->button_list.at(i)->data_id = i;
	}

	//EWindow::window_editor->count_of_floors--;

	



	EWindow::window_editor->refresh_autobuilding();
}

void EBA::action_add_new_floor(EButton* _b, float _d)
{
	for (EButton* b : EWindow::window_editor->link_to_floors_array->button_list)
	{
		if (!b->is_active)
		{
			b->is_active = true;
			b->gabarite = NULL;

			break;
		}
	}

	if (EWindow::window_editor->selected_entity != NULL)
	{
		EWindow::window_editor->selected_entity->autobuilding_floor_list.push_back(new Entity::building_autogen_floor);

		Entity::update_building_autogenerator_massive(EWindow::window_editor->selected_entity);
	}
}

void EBA::action_move_floor_order(EButton* _b, float _d)
{
	Entity::building_autogen_floor* swap;

	//<<<
	if ((_b->data_id == 0) & (EWindow::window_editor->autobuilding_selected_floor > 0))
	{
		swap = EWindow::window_editor->selected_entity->autobuilding_floor_list.at(EWindow::window_editor->autobuilding_selected_floor);

		EWindow::window_editor->selected_entity->autobuilding_floor_list.at(EWindow::window_editor->autobuilding_selected_floor)
		=
		EWindow::window_editor->selected_entity->autobuilding_floor_list.at(EWindow::window_editor->autobuilding_selected_floor - 1);

		EWindow::window_editor->selected_entity->autobuilding_floor_list.at(EWindow::window_editor->autobuilding_selected_floor - 1)
		=
		swap;
		//EWindowEditor::link_to_floors_array

		EWindow::window_editor->autobuilding_selected_floor--;
	}

	//>>>
	if ((_b->data_id == 1) & (EWindow::window_editor->autobuilding_selected_floor < EWindow::window_editor->selected_entity->autobuilding_floor_list.size() - 1))
	{
		swap = EWindow::window_editor->selected_entity->autobuilding_floor_list.at(EWindow::window_editor->autobuilding_selected_floor);

		EWindow::window_editor->selected_entity->autobuilding_floor_list.at(EWindow::window_editor->autobuilding_selected_floor)
			=
			EWindow::window_editor->selected_entity->autobuilding_floor_list.at(EWindow::window_editor->autobuilding_selected_floor + 1);

		EWindow::window_editor->selected_entity->autobuilding_floor_list.at(EWindow::window_editor->autobuilding_selected_floor + 1)
			=
			swap;
		//EWindowEditor::link_to_floors_array
		EWindow::window_editor->autobuilding_selected_floor++;
	}

	EWindow::window_editor->refresh_autobuilding();
}

void EBA::action_select_floor(EButton* _b, float _d)
{
	EWindow::window_editor->autobuilding_selected_floor = _b->data_id;

	//EWindow::window_editor->select_new_floor();
	EWindow::window_editor->refresh_autobuilding();

	Entity::assembly_autobuilding_sprites(EWindow::window_editor->selected_entity);
	Entity::update_building_autogenerator_massive(EWindow::window_editor->selected_entity);

	EWindow::window_editor->move_mode = EWindowEditor::MoveMode::MoveFloor;

	//std::cout << "floor count: " << std::to_string(EWindow::window_editor->count_of_floors) << std::endl;
}

void EBA::action_select_texture_variant(EButton* _b, float _d)
{
	EWindow::window_editor->autobuilding_selected_texture_variant = _b->data_id;
	//EWindow::window_editor->select_new_variant();
	EWindow::window_editor->refresh_autobuilding();
	EWindow::window_editor->move_mode = EWindowEditor::MoveMode::MoveTexture;
}

void EBA::action_assembly_autobuilding(EButton* _b, float _d)
{
	Entity::assembly_autobuilding_sprites(EWindow::window_editor->selected_entity);
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
