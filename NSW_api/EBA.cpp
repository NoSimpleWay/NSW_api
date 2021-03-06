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

void EBA::action_set_sprite_texture_for_autobuilding(EButton* _b, float _d)
{
	EWindowEditor* ed = EWindow::window_editor;

	if (EWindow::window_editor->object_variant != NULL)
	{
		EWindow::window_editor->object_variant->texture = _b->gabarite;
		_b->description_text = _b->gabarite->name;
	}


	ed->selected_entity->autobuilding_floor_list.at(ed->autobuilding_selected_floor)->
	wall_list.at(ed->autobuilding_selected_wall)->
	texture_variant_list.at(ed->autobuilding_selected_texture_variant)->
	supermap
	=
	ETextureAtlas::get_supermap_from_regular_texture_path(_b->gabarite->name, EWindow::default_texture_atlas);


	ed->link_to_texture_variant_array->button_list.at(ed->autobuilding_selected_texture_variant)->gabarite = _b->gabarite;

	if (!glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		EWindow::window_search_brick->is_active = false;
	}

}

void EBA::action_open_select_texture_window(EButton* _b, float _d)
{

	EWindow::window_search_brick->is_active = true;
	EWindow::window_search_brick->search_mode = EWindowSearchBrick::SearchMode::SEARCH_TEXTURE;

	EWindow::window_search_brick->update_search(EWindow::window_search_brick->link_to_input);

	for (EButton* b : EWindow::window_search_brick->brick_button)
	{b->action_on_left_click = &EBA::action_set_sprite_texture_for_autobuilding;}



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
		w_string += "\t";
		w_string += std::to_string(*e->position_x);

		w_string += "\t";
		w_string += std::to_string(*e->position_y);

		w_string += "\t";
		w_string += std::to_string(*e->position_z);
	w_string += "\n";


	
	for (int i = 0; i < e->autobuilding_floor_order.size(); i++)
	{
		w_string += "floor_order\t";
		w_string += std::to_string(e->autobuilding_floor_order.at(i));
		w_string += "\n";
	}

	for (int i = 0; i < e->autobuilding_floor_order.size(); i++)
	{
		w_string += "floor_left_border\t";

		if (*e->autobuilding_left_border.at(i))
		{w_string += "true";}
		else
		{w_string += "false";}

		w_string += "\n";
	}

	for (int i = 0; i < e->autobuilding_floor_order.size(); i++)
	{
		w_string += "floor_right_border\t";

		if (*e->autobuilding_right_border.at(i))
		{w_string += "true";}
		else
		{w_string += "false";}

		w_string += "\n";
	}

	for (int i = 0; i < e->autobuilding_floor_order.size(); i++)
	{
		w_string += "floor_generate_offset_x\t";

		if (*e->autobuilding_generate_offset_x.at(i))
		{w_string += "true";}
		else
		{w_string += "false";}

		w_string += "\n";
	}

	for (int i = 0; i < e->autobuilding_floor_order.size(); i++)
	{
		w_string += "floor_generate_offset_y\t";

		if (*e->autobuilding_generate_offset_y.at(i))
		{w_string += "true";}
		else
		{w_string += "false";}

		w_string += "\n";
	}
	
	//EDataWatcher::vectorizator(e->sprite_list, );

	for (ESprite* spr : e->sprite_list)
	{
		
		w_string += "ADD_NEW_SPRITE\n";



		if (*spr->rotate_by_move) { w_string += "*rotate_by_move\n"; }
		if (*spr->is_shadow) { w_string += "*shadow\n"; }
		if (*spr->wall_mode) { w_string += "*wall_mode\n"; }
		if (*spr->rotate_by_target_gun) { w_string += "*target_gun\n"; }
		if (*spr->is_mirrored) { w_string += "*texture_mirrored\n";}


		//order = 0;
		for (ESprite::sprite_struct* str : spr->sprite_struct_list)
		{
			

			if (str->gabarite != NULL)
			{
				w_string += "add_new_texture\t";
				w_string += str->gabarite->name;
				w_string += "\n";
			}

			for (EDataWatcher::data_watcher_struct<float*>* dws : str->data_watcher_float_list)
			{
				w_string += dws->name;


				for (float* f : dws->watcher_address)
				{
					w_string += "\t";
					w_string += std::to_string(*f);
				}

				w_string += "\n";
			}
		



			//order++;
		}
	}

	int id = 0;
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



		w_string += "floor_name\t";
			//w_string += std::to_string(EWindow::window_editor->link_to_floors_array->button_list.at(id)->text);
			w_string += *f->name;
		w_string += "\n";

		id = 0;
		for (EColor* c : f->color_matrix)
		{
			
			w_string += "wall_color\t";
				
				//w_string += std::to_string(id)	+ "\t";
				w_string += std::to_string(c->red)		+ "\t";
				w_string += std::to_string(c->green)	+ "\t";
				w_string += std::to_string(c->blue)		+ "\t";

				w_string += std::to_string(c->alpha);
			w_string += "\n";

			id++;
		}

		if (*f->wall_window_is_stretched)
		{
			w_string += "window_is_stretched";
			w_string += "\n";
		}

		w_string += "floor_additional_distance_between_window_x\t";
		w_string += std::to_string(*f->window_distance_x);
		w_string += "\n";

		w_string += "floor_additional_distance_between_window_y\t";
		w_string += std::to_string(*f->window_distance_y);
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

			w_string += "wall_element_color\t";
				w_string += std::to_string(w->element_color->red)			+ "\t";
				w_string += std::to_string(w->element_color->green)			+ "\t";
				w_string += std::to_string(w->element_color->blue)			+ "\t";
				w_string += std::to_string(*w->element_color_multiplier);
			w_string += "\n";
		}

		id++;
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

	for (EWindowEditor::terrain_element_struct* tes : EWindowEditor::terrain_element_list)
	{
		w_string += "#terrain_element";
		w_string += "\n";

		for (int i = 0; i < tes->terrain_variant.size(); i++)
		{
			w_string += "#terrain_element_texture\t";

			if (tes->terrain_variant.at(i) != NULL)
			{w_string += tes->terrain_variant.at(i)->name;}
			else
			{w_string += "NULL";}

			w_string += "\t";

			w_string += std::to_string(tes->id.at(i));
			w_string += "\n";
		}
	}

		for (int j=0; j<ECluster::CLUSTER_DIM; j++)
		for (int i = 0; i < ECluster::CLUSTER_DIM; i++)
		for (Entity* e : ECluster::clusters[j][i]->entity_list)
		if(!*e->is_bullet) {EBA::save_to_file(w_string, e, order, false);}

	writer << w_string;
	writer.close();

	std::string w_result = "";
	std::string w_alphabet = "";
	std::string final_string = "";
	std::vector <std::string> alphabet;
	int alphabet_id = 0;
	std::string subs = "";

	alphabet.clear();
	for (int i = 0; i < w_string.length(); i ++)
	{
		if (i % 10000 == 0)
		{
			logger_param("i ", i);
		}

		
		if ((w_string.at(i) == '\t')||(w_string.at(i) == '\n'))
		{
			if (w_string.at(i) == '\n') { subs += '\n'; }

			alphabet_id = -1;
			for (int j = 0; j < alphabet.size(); j++)
			{
				if (alphabet.at(j) == subs)
				{
					alphabet_id = j;
					break;
				}
			}

			if (alphabet_id == -1)
			{
				alphabet.push_back(subs);

				w_result += (char)alphabet.size();

				if (alphabet.size() > 255)
				{
					final_string += "^begin_alphabet^\n";
					alphabet_id = 0;
					for (std::string s : alphabet)
					{
						
						//final_string += '[' + std::to_string(alphabet_id) + ']' + s + '\n';
						final_string += s + '\t';
						

						alphabet_id++;
					}
					final_string += "^end_alphabet^\n";
					final_string += w_result;

					w_result = "";
					alphabet.clear();
				}
			}
			else
			{
				w_result += (char)alphabet_id;
			}

			subs = "";
		}
		else
		{subs += w_string.at(i);}

		

		//if (w_string.at(i) == '\n')
		//{w_result += '\n';}
	}

	if (alphabet.size() > 0)
	{
		final_string += "@begin_alphabet@\n";

		alphabet_id = 0;
		for (std::string s : alphabet)
		{
			final_string += '[' + std::to_string(alphabet_id) + ']' + s + '\n';
			alphabet_id++;
		}

		final_string += "@end_alphabet@\n";
	}
	final_string += w_result;

	for (int z = 0; z < 0; z++)
	{
		alphabet.clear();

		w_result = "";
		w_alphabet = "";
		final_string = "";

		//read each symbol and set pair
		for (int i = 0; i < w_string.length(); i += 2)
		{
			//pair of symbols
			std::string portion = w_string.substr(i, 2);

			alphabet_id = -1;

			//search pair in alphabet
			for (int i = 0; i < alphabet.size(); i++)
			{
				if (alphabet.at(i) == portion)
				{
					alphabet_id = i;
					break;
				}
			}

			//new pair
			if (alphabet_id == -1)
			{
				alphabet.push_back(portion);

				w_result += (char)alphabet.size();
				w_alphabet += portion;

				if (alphabet.size() > 255)
				{
					alphabet_id = 0;

					std::string nu = "";

					if (w_result.length() < 10000)		{ nu += "0"; }
					if (w_result.length() < 1000)		{ nu += "0"; }
					if (w_result.length() < 100)		{ nu += "0"; }
					if (w_result.length() < 10)			{ nu += "0"; }
					nu += std::to_string(w_result.length());
					nu += "";

					final_string += "256" + w_alphabet + nu + w_result;

					w_result = "";
					w_alphabet = "";
					alphabet.clear();
				}
			}
			else
			//exist pair
			{
				w_result += (char)alphabet_id;
			}
		}

		//w_alphabet = "# alphabet_begin #\n";

		final_string += w_alphabet + w_result;

		//w_alphabet += "# alphabet_end #\n";

		//working string is compression result
		w_string = final_string;
	}

	//writer;
	writer.open("test/map_compressor.txt");
		w_string = "";
	writer << final_string;
	writer.close();

	writer.open("test/map_t.txt");
		w_string = "";

		for (int i = 0; i < EPath::PATH_DIM; i++)
		for (int j = 0; j < EPath::PATH_DIM; j++)
		{
			w_string += (char)EWindow::window_test->terrain[j][i];
		}

		w_string += "�";

		for (int i = 0; i < EPath::PATH_DIM; i++)
		for (int j = 0; j < EPath::PATH_DIM; j++)
		{
			w_string += (char)EWindow::window_test->terrain_layer[j][i];
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

		EWindowEditor::terrain_element_struct* just_created_terrain_element = NULL;
		EGabarite* just_created_terrain_variant;

		int terrain_element_list_id = 0;
		int terrain_variant_list_id = 0;

		int wall_id = 0;
		int wall_color_id = 0;

		int floor_id = 0;
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
				
				if (EFile::data_array[i] == "#terrain_element")
				{
					just_created_terrain_element = EWindowEditor::terrain_element_list.at(terrain_element_list_id);
					
					terrain_element_list_id++;
					terrain_variant_list_id = 0;
				}

				if (EFile::data_array[i] == "#terrain_element_texture")
				{
					if (just_created_terrain_element != NULL)
					{
						i++;

						if (EFile::data_array[i] != "NULL")
						{just_created_terrain_variant = ETextureAtlas::put_texture_to_atlas(EFile::data_array[i], EWindow::default_texture_atlas);}
						else
						{just_created_terrain_variant = NULL;}

						just_created_terrain_element->terrain_variant.at(terrain_variant_list_id) = just_created_terrain_variant;

						i++;

						just_created_terrain_element->id.at(terrain_variant_list_id) = std::stoi(EFile::data_array[i]);

					}

					terrain_variant_list_id++;
				}

				if (EFile::data_array[i] == "ADD_NEW_ENTITY")
				{
					wall_id = 0;
					floor_id = 0;
					just_created_entity = new Entity();
					i++; *just_created_entity->position_x = std::stof(EFile::data_array[i]);
					i++; *just_created_entity->position_y = std::stof(EFile::data_array[i]);

					just_created_entity->autobuilding_floor_order.clear();
					just_created_entity->autobuilding_left_border.clear();
					just_created_entity->autobuilding_right_border.clear();
					just_created_entity->autobuilding_generate_offset_x.clear();
					just_created_entity->autobuilding_generate_offset_y.clear();

				}

				if ((EFile::data_array[i] == "*entity_controlled_by_player") && (just_created_entity != NULL))
				{
					*just_created_entity->controlled_by_player = true;
					//EWindow::window_test->link_to_player = just_created_entity;
					//EWindow::window_editor->selected_entity = just_created_entity;
				}

				if ((EFile::data_array[i] == "floor_order") && (just_created_entity != NULL))
				{i++; just_created_entity->autobuilding_floor_order.push_back(std::stoi(EFile::data_array[i]));}

				if ((EFile::data_array[i] == "floor_left_border") && (just_created_entity != NULL))
				{
					i++;
					if (EFile::data_array[i] == "true")
					{just_created_entity->autobuilding_left_border.push_back(new bool(true));}

					if (EFile::data_array[i] == "false")
					{just_created_entity->autobuilding_left_border.push_back(new bool(false));}
				}

				if ((EFile::data_array[i] == "floor_right_border") && (just_created_entity != NULL))
				{
					i++;
					if (EFile::data_array[i] == "true")
					{just_created_entity->autobuilding_right_border.push_back(new bool(true));}

					if (EFile::data_array[i] == "false")
					{just_created_entity->autobuilding_right_border.push_back(new bool(false));}
				}

				if ((EFile::data_array[i] == "floor_generate_offset_x") && (just_created_entity != NULL))
				{
					i++;
					if (EFile::data_array[i] == "true")
					{just_created_entity->autobuilding_generate_offset_x.push_back(new bool(true));}

					if (EFile::data_array[i] == "false")
					{just_created_entity->autobuilding_generate_offset_x.push_back(new bool(false));}
				}

				if ((EFile::data_array[i] == "floor_generate_offset_y") && (just_created_entity != NULL))
				{
					i++;
					if (EFile::data_array[i] == "true")
					{just_created_entity->autobuilding_generate_offset_y.push_back(new bool(true));}

					if (EFile::data_array[i] == "false")
					{just_created_entity->autobuilding_generate_offset_y.push_back(new bool(false));}
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

					/*just_created_gabarite = ETextureAtlas::put_texture_to_atlas
					(
						EFile::data_array[i].substr(0, EFile::data_array[i].length() - 4) + "#supermap.png",
						EWindow::default_texture_atlas
					);*/

					just_created_gabarite = ETextureAtlas::get_supermap_from_regular_texture_path(EFile::data_array[i], EWindow::default_texture_atlas);


					just_create_sprite_struct->supermap = just_created_gabarite;
				}

				if (just_create_sprite_struct != NULL)
				for (EDataWatcher::data_watcher_struct<float*>* dws : just_create_sprite_struct->data_watcher_float_list)
				{
					if (dws->name == EFile::data_array[i]) { i++; *dws->watcher_address.at(0) = std::stof(EFile::data_array[i]); }
				}

				
				if (just_created_floor != NULL)
				{ 
					if (EFile::data_array[i] == "floor_additional_distance_between_window_x")
					{i++; *just_created_floor->window_distance_x = std::stof(EFile::data_array[i]);}
				
					if (EFile::data_array[i] == "floor_additional_distance_between_window_y")
					{i++; *just_created_floor->window_distance_y = std::stof(EFile::data_array[i]);}
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
					if (*just_created_entity->mass_pointer <= 0) { *just_created_entity->mass_pointer = 0.1f; }
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
					i++;  std::cout << "|" << EFile::data_array[i] << "|" << std::endl; if (EFile::data_array[i] != "")		*just_created_floor->bottom_roof_offset_multiplier = std::stof(EFile::data_array[i]);
					i++;  std::cout << "|" << EFile::data_array[i] << "|" << std::endl; if (EFile::data_array[i] != "")		*just_created_floor->up_roof_offset_multiplier = std::stof(EFile::data_array[i]);
					i++;  std::cout << "|" << EFile::data_array[i] << "|" << std::endl; if (EFile::data_array[i] != "")		*just_created_floor->horizontal_roof_offset_multiplier	= std::stof(EFile::data_array[i]);

					wall_id = 0;
					wall_color_id = 0;
				}

				
				if ((EFile::data_array[i] == "wall_color") & (just_created_floor != NULL))
				{
					i++;  just_created_floor->color_matrix.at(wall_color_id)->red = std::stof(EFile::data_array[i]);
					i++;  just_created_floor->color_matrix.at(wall_color_id)->green = std::stof(EFile::data_array[i]);
					i++;  just_created_floor->color_matrix.at(wall_color_id)->blue = std::stof(EFile::data_array[i]);

					wall_color_id++;
				}

				if (EFile::data_array[i] == "floor_name")
				{
					//i++; EWindow::window_editor->link_to_floors_array->button_list.at(floor_id)->text = EFile::data_array[i];
					i++; *just_created_floor->name = EFile::data_array[i];

					floor_id++;
				}

				if ((EFile::data_array[i] == "window_is_stretched") & (just_created_floor != NULL))
				{*just_created_floor->wall_window_is_stretched = true;}
				
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

				if (EFile::data_array[i] == "wall_element_color")
				{
					i++;  just_created_wall->element_color->red				= std::stof(EFile::data_array[i]);
					i++;  just_created_wall->element_color->green			= std::stof(EFile::data_array[i]);
					i++;  just_created_wall->element_color->blue			= std::stof(EFile::data_array[i]);
					
					i++;  *just_created_wall->element_color_multiplier		= std::stof(EFile::data_array[i]);
				}
			}
		}
	}
}

void EBA::action_load_map(EButton* _b, float _d)
{

	//EWindowEditor::terrain_element_list.clear();

	ifstream myfile;

	if (_b != NULL)
	{myfile.open(_b->data_string + ".txt");}
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

	EWindowEditor::select_new_terrain();
	EWindowEditor::select_new_terrain_variant();
	EWindowEditor::reinit_terrain_matrix();

	std::string t_s_data = "";
	char* tsdata = new char[EPath::PATH_DIM * EPath::PATH_DIM];

	if (_b != NULL)
	{myfile.open(_b->data_string + "_t.txt");}
	else
	{myfile.open("test/map_t.txt");}

		/*while (getline(myfile, line))
		{

		}*/
		myfile.get(tsdata, EPath::PATH_DIM * EPath::PATH_DIM);
		
		
		for (int i = 0; i < EPath::PATH_DIM; i++)
		for (int j = 0; j < EPath::PATH_DIM; j++)
		{
			EWindow::window_test->terrain[j][i] = (short)(tsdata[j + i * EPath::PATH_DIM]);
		}

		remove(tsdata);
		tsdata = new char[EPath::PATH_DIM * EPath::PATH_DIM + 1];

		myfile.get(tsdata, EPath::PATH_DIM * EPath::PATH_DIM);
		for (int i = 0; i < EPath::PATH_DIM; i++)
		for (int j = 0; j < EPath::PATH_DIM; j++)
		{
			//EWindow::window_test->terrain_layer[j][i] = -1;
			EWindow::window_test->terrain_layer[j][i] = (short)(tsdata[j + i * EPath::PATH_DIM + 2]);
		}

	myfile.close();

	EWindow::window_test->generate_terrain();

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

void EBA::action_set_button_value_short_to_address(EButton* _b, float _d)
{
	if ((_b->target_address_for_short != NULL) & (*_b->is_checkbox))
	{
		*_b->target_address_for_short = short(*_b->is_checked);
	}
}

void EBA::action_set_button_value_int_to_address(EButton* _b, float _d)
{
	if (((_b->is_slider) || (*_b->is_radial_button)) & (_b->target_address_for_int != NULL))
	{
		*_b->target_address_for_int = (int)_b->slider_value;
	}

	if ((_b->target_address_for_int != NULL) & (_b->is_drop_list))
	{
		*_b->target_address_for_int = _b->selected_element;
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

void EBA::action_set_button_value_gabarite_to_address(EButton* _b, float _d)
{
	if (_b->target_address_for_gabarite != NULL)
	{
		*_b->target_address_for_gabarite = _b->gabarite;
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

	int id = 0;
	for (EButton* b : EWindow::window_editor->link_to_texture_variant_array->button_list)
	{
		if (!b->is_active)
		{
			b->is_active = true;
			b->gabarite = EGraphicCore::gabarite_ERROR;

			/*if (EWindowEditor::object_variant != NULL)
			{
				EWindowEditor::object_variant->texture = EGraphicCore::gabarite_ERROR;
				EWindowEditor::object_variant->supermap = EGraphicCore::gabarite_supermap_placeholder;
			}*/

			break;
		}

		id++;
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

		if (EWindow::window_editor->autobuilding_selected_wall == Entity::WallElementIndex::WEI_SHADOW)
		{ tv->texture = EGraphicCore::gabarite_white_pixel; }
		else
		{
			tv->texture = EGraphicCore::gabarite_ERROR;
			tv->supermap = EGraphicCore::gabarite_supermap_placeholder;
		}
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

	EWindow::window_editor->change_drop_button_container();
}

void EBA::action_add_new_floor(EButton* _b, float _d)
{
	Entity::building_autogen_floor* jcf = new Entity::building_autogen_floor;

	if (EWindow::window_editor->selected_entity != NULL)
	{
		EWindow::window_editor->selected_entity->autobuilding_floor_list.push_back(jcf);
		*jcf->name = "floor";

		//Entity::update_building_autogenerator_massive(EWindow::window_editor->selected_entity);
	}

	for (EButton* b : EWindow::window_editor->link_to_floors_array->button_list)
	{
		if (!b->is_active)
		{
			b->is_active = true;
			b->gabarite = NULL;

			b->text = *jcf->name;
			b->target_address_for_string = jcf->name;

			break;
		}
	}

	EWindow::window_editor->change_drop_button_container();
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

	EWindow::window_editor->change_drop_button_container();
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
	//(*_b->target_address_for_gabarite)->name = "x";
	logger_param("texture link:", (*_b->target_address_for_gabarite)->name);

	//*_b->target_address_for_gabarite = EGraphicCore::gabarite_radial_button;
}

void EBA::action_assembly_autobuilding(EButton* _b, float _d)
{
	Entity::assembly_autobuilding_sprites(EWindow::window_editor->selected_entity);
}

void EBA::action_start_input(EButton* _b, float _d)
{
	_b->is_input_mode_active = true;
}

void EBA::action_refresh_drop_autobuilding_list(EButton* _b, float _d)
{
	EWindow::window_editor->change_drop_button_container();

	if (_b->target_address_for_string != NULL)
	{
		*_b->target_address_for_string = _b->text;
	}
}

void EBA::action_wall_color_noise(EButton* _b, float _d)
{
	//if (EWindow::window_editor->object_wall_color != NULL)
	//if (EWindow::window_editor->selected_entity != NULL)
	if (EWindow::window_editor->object_floor != NULL)
	{
		for (EColor* c : EWindow::window_editor->object_floor->color_matrix)
		{
			c->red += ((rand() % 1001 / 1000.0f) - 0.5f) / 20.0f;
			c->green += ((rand() % 1001 / 1000.0f) - 0.5f) / 20.0f;
			c->blue += ((rand() % 1001 / 1000.0f) - 0.5f) / 20.0f;
		}
	}
}

void EBA::action_wall_color_blur(EButton* _b, float _d)
{
	int color_count = 0;
	float color_summ = 0.0f;

	if (EWindow::window_editor->object_floor != NULL)
	{
		//for (EColor* c : EWindow::window_editor->object_floor->color_matrix)


		for (int i=0; i <= EWindow::window_editor->autobuilding_selected_color_matrix; i++)
		{
			//EColor::get_interpolate_color(EWindow::window_editor->object_floor->color_matrix.at(i), 0.2f, EWindow::window_editor->object_floor->color_matrix.at(i))
			color_count = 0;
			color_summ = 0.0f;

			//up red
				if (i < EWindow::window_editor->autobuilding_selected_color_matrix)
				{color_summ += EWindow::window_editor->object_floor->color_matrix.at(i + 1)->red; color_count++;}

			//mid red
				color_summ += EWindow::window_editor->object_floor->color_matrix.at(i)->red; color_count++;

			//down red
			if (i > 0)
				{color_summ += EWindow::window_editor->object_floor->color_matrix.at(i - 1)->red; color_count++;}

				EWindow::window_editor->object_floor->color_matrix.at(i)->red = color_summ / (float)color_count;



			color_count = 0;
			color_summ = 0.0f;

				//up green
				if (i < EWindow::window_editor->autobuilding_selected_color_matrix)
				{
					color_summ += EWindow::window_editor->object_floor->color_matrix.at(i + 1)->green; color_count++;
				}

				//mid green
				color_summ += EWindow::window_editor->object_floor->color_matrix.at(i)->green; color_count++;

				//down green
				if (i > 0)
				{
					color_summ += EWindow::window_editor->object_floor->color_matrix.at(i - 1)->green; color_count++;
				}

				EWindow::window_editor->object_floor->color_matrix.at(i)->green = color_summ / (float)color_count;


				color_count = 0;
				color_summ = 0.0f;

				//up blue
				if (i < EWindow::window_editor->autobuilding_selected_color_matrix)
				{
					color_summ += EWindow::window_editor->object_floor->color_matrix.at(i + 1)->blue; color_count++;
				}

				//mid blue
				color_summ += EWindow::window_editor->object_floor->color_matrix.at(i)->blue; color_count++;

				//down blue
				if (i > 0)
				{
					color_summ += EWindow::window_editor->object_floor->color_matrix.at(i - 1)->blue; color_count++;
				}

				EWindow::window_editor->object_floor->color_matrix.at(i)->blue = color_summ / (float)color_count;
		}
	}
}

void EBA::action_set_terrain_texture(EButton* _b, float _d)
{

}

void EBA::action_reset_floor_wall_color(EButton* _b, float _d)
{
	if
	(
		(EWindow::window_editor->selected_entity != NULL)
		&&
		(EWindow::window_editor->object_floor != NULL)
		&&
		(_b->data_id >= 0)
		&&
		(_b->data_id < EWindow::window_editor->object_floor->color_matrix.size())
	)
	{
		EWindow::window_editor->object_floor->color_matrix.at(_b->data_id)->red		= 0.5f;
		EWindow::window_editor->object_floor->color_matrix.at(_b->data_id)->green	= 0.5f;
		EWindow::window_editor->object_floor->color_matrix.at(_b->data_id)->blue	= 0.5f;
	}
}

void EBA::action_select_new_terrain_variant(EButton* _b, float _d)
{
	EWindowEditor::object_terrain_variant = _b;
	EWindowEditor::select_new_terrain_variant();
}

void EBA::action_select_new_terrain(EButton* _b, float _d)
{
	EWindowEditor::object_terrain = _b;
	EWindowEditor::select_new_terrain();
}

void EBA::action_add_new_terrain_variant_button(EButton* _b, float _d)
{
	for (EButton* b : EWindowEditor::terrain_texture_variant_button_link)
	{
		if (!b->is_active)
		{
			b->is_active = true;
			break;
		}
	}
}

void EBA::action_add_new_terrain_button(EButton* _b, float _d)
{
	for (EButton* b : EWindowEditor::terrain_texture_button_link)
	{
		if (!b->is_active)
		{
			b->is_active = true;
			break;
		}
	}
}

void EBA::action_open_select_terrain_window(EButton* _b, float _d)
{

	logger("try open brick window");
	EWindow::window_search_brick->is_active = true;
	EWindow::window_search_brick->search_mode = EWindowSearchBrick::SearchMode::SEARCH_TEXTURE;

	EWindow::window_search_brick->update_search(EWindow::window_search_brick->link_to_input);

	for (EButton* b : EWindow::window_search_brick->brick_button)
	{
		b->action_on_left_click = &EBA::action_set_sprite_texture_for_terrain;
	}
}

void EBA::action_set_sprite_texture_for_terrain(EButton* _b, float _d)
{
	if (EWindowEditor::object_terrain_variant != NULL)
	{
		EWindowEditor::object_terrain_variant->gabarite = _b->gabarite;

		if (EWindowEditor::object_terrain_variant != NULL)
		{
			EWindowEditor::terrain_element_list.at(EWindowEditor::object_terrain->data_id)->
			terrain_variant.at(EWindowEditor::object_terrain_variant->data_id)
			=
			_b->gabarite;
		}
	}

	if (!glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		EWindow::window_search_brick->is_active = false;
	}

	EWindowEditor::reinit_terrain_matrix();
}

void EBA::action_destroy_terrain_texture(EButton* _b, float _d)
{
	_b->gabarite = NULL;

	for (EButton* b : EWindowEditor::terrain_texture_variant_button_link)
	{
		b->is_active = false;
	}

	for (int i=0; i<EWindowEditor::terrain_element_list.at(_b->data_id)->terrain_variant.size(); i++)
	{
		EWindowEditor::terrain_element_list.at(_b->data_id)->terrain_variant.at(i) = NULL;
	}

	EWindowEditor::reinit_terrain_matrix();
	
}

void EBA::action_destroy_terrain_texture_variant(EButton* _b, float _d)
{
	if (EWindowEditor::object_terrain != NULL)
	{
		EWindowEditor::terrain_element_list.at(EWindowEditor::object_terrain->data_id)->terrain_variant.at(_b->data_id);
	}

	_b->gabarite = NULL;

	EWindowEditor::reinit_terrain_matrix();
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
