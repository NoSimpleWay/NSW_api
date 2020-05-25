#pragma once

#include <vector>
#include "NSW_api/EGabarite.h"
#include "NSW_api/Batcher.h"
#include "EPath.h"


class ECluster;
class ESprite;
class EItem;
class EItemAttribute;


class Entity
{
public:

	/////////////////////////////////////////////////////////
	typedef void (*HIT_ACTION)(Entity* _a, Entity* _b, int _side);
	enum Side { HIT_SIDE_NONE, HIT_SIDE_UP, HIT_SIDE_RIGHT, HIT_SIDE_DOWN, HIT_SIDE_LEFT };

	

	static std::vector<HIT_ACTION> HIT_ACTIONS_LIST;
	static std::vector < std::string> HIT_ACTION_NAME_LIST;

	static int search_hit_action(std::string _text);
	static std::string get_hit_action_name(HIT_ACTION _action);



	HIT_ACTION action_on_hit;
	HIT_ACTION action_on_hited;
	
	static void test_hit_action_destroy_touch(Entity* _a, Entity* _b, int _side);
	static void test_hit_action_self_destroy_on_hit(Entity* _a, Entity* _b, int _side);
	/////////////////////////////////////////////////////////

	float* position_x = new float();
	float* position_y = new float();

	float* speed_x = new float();
	float* speed_y = new float();

	float* real_speed_x = new float();
	float* real_speed_y = new float();

	float* mass = new float(10.0f);
	bool* inmovable = new bool(false);

	float* collision_up		= new float(20.0f);
	float* collision_down	= new float(20.0f);
	float* collision_left	= new float(20.0f);
	float* collision_right	= new float(20.0f);

	float* shoot_cooldown = new float(0.0f);

	bool* already_updated = new bool(false);
	int* updates_count = new int(0);

	int* prev_cluster_x = new int(0);
	int* prev_cluster_y = new int(0);

	bool* already_moved_x = new bool(false);
	bool* already_moved_y = new bool(false);

	bool* need_change_cluster = new bool(false);
	bool* need_remove = new bool(false);

	bool* is_left_side_collided = new bool(false);
	bool* is_right_side_collided = new bool(false);
	bool* is_up_side_collided = new bool(false);
	bool* is_down_side_collided = new bool(false);

	int* target_angle_id = new int(0);

	

	Entity();
	~Entity();

	static std::vector<Entity*> entity_list;


	std::vector <EGabarite*> body;
	std::vector <float> body_offset_x;
	std::vector <float> body_offset_y;

	bool body_rotate_by_move = false;

	bool controlled_by_ai = false;
	bool controlled_by_player = false;

	std::vector<ESprite*> sprite_list;

	static void draw_sprite(Entity* _e, Batcher* _b, float _d, bool _is_shadow_mode, bool _transparent_is_height);
	//static void draw_shadow_sprite(Entity* _e, Batcher* _b, float _d);

	bool* is_bullet = new bool(false);


	static std::vector <Entity*> entity_collection_list;

	static void update_path_block(Entity* _e);
	static void spread_path_block(Entity* _e);

	bool* have_lifetime = new bool(false);
	float* lifetime = new float(1.0f);

	float* shadow_tall = new float(100.0f);

	float* target_position_x = new float(0.0f);
	float* target_position_y = new float(0.0f);

	/*-------attribute section-------*/

	enum EntityCurrentAttribute
	{
		CURRENT_LIFE,
		CURRENT_SHIELD,
		CURRENT_SHIELD_OVERLOAD_CAPACITY,
		CURRENT_SHIELD_OVERLOAD_DURATION,

		/*---------DO NOT TOUCH!-----------*/
		/* mark of enum size*/_LAST_ELEMENT_OF_CA
		/*---------DO NOT TOUCH!-----------*/
	};


	//names of all attributes
	enum EAttr
	{
		EA_LIFE,
		EA_SHIELD,
		ENTITY_ATTRIBUTE_SHIELD_REGEN,

		ENTITY_ATTRIBUTE_SHIELD_OVERLOAD_CAPACITY,
		ENTITY_ATTRIBUTE_SHIELD_OVERLOAD_DURATION,

		ENTITY_ATTRIBUTE_MASS,
		ENTITY_ATTRIBUTE_SPEED,
		ENTITY_ATTRIBUTE_DRAG,

		/*---------DO NOT TOUCH!-----------*/
		/* mark of enum size*/_LAST_ELEMENT_OF_EA
		/*---------DO NOT TOUCH!-----------*/
	};








	//all attributes, who can change, and have maximum (life, shield, overload)
	std::vector <float> eattr_current = std::vector<float>(EntityCurrentAttribute::_LAST_ELEMENT_OF_CA, 0.0f);

	//list of all attributes
	std::vector <float> eattr_BASE = std::vector<float>(EAttr::_LAST_ELEMENT_OF_EA, 0.0f);

	//increase attribute (accumulate calues and multiply. Example: +15% increased life, + 40% increased life, + 20% increased life = 0.15 + 0.4 + 0.2 = +75% more life
	std::vector <float> eattr_INCREASE = std::vector<float>(EAttr::_LAST_ELEMENT_OF_EA, 0.0f);

	//more attribute (multiply between bomuses. Example: 15% more life, 40% more life, 20% more life = 1.15 * 1.4 * 1.2 = 93.2% more life
	std::vector <float> eattr_MORE = std::vector<float>(EAttr::_LAST_ELEMENT_OF_EA, 0.0f);

	//attribute after all bonuses
	std::vector <float> eattr_TOTAL = std::vector<float>(EAttr::_LAST_ELEMENT_OF_EA, 0.0f);

	float* hp_pointer;
	float* max_hp_pointer;

	float* shield_pointer;
	float* max_shield_pointer;

	float* shield_overload_capacity_pointer;
	float* max_shield_overload_capacity_pointer;

	float* shield_overload_duration_pointer;
	float* max_shield_overload_duration_pointer;

	static void update_entity_attributes(Entity* _e);
};


class ECluster
{
public:
	ECluster();
	~ECluster();

	std::vector<Entity*> entity_list;
	

	//----------STATIC----------------------------
	static const int CLUSTER_SIZE = 200;
	static const int CLUSTER_DIM = 100;

	static void put_entity(Entity* _e, float _x, float _y);
	static void put_entity(Entity* _e);

	static ECluster* clusters[CLUSTER_DIM][CLUSTER_DIM];

	bool static collision_left(Entity* _a, Entity* _b);
	bool static collision_right(Entity* _a, Entity* _b);
	bool static collision_down(Entity* _a, Entity* _b);
	bool static collision_up(Entity* _a, Entity* _b);

	int static cluster_on_mouse_x;
	int static cluster_on_mouse_y;

	void static get_cluster_on_mouse_coords();
};

class ESprite
{
public:
	std::vector<EGabarite*> gabarite;
	std::vector<EGabarite*> supermap;

	std::vector<float> offset_x;
	std::vector<float> offset_y;
	std::vector<float> offset_z;

	std::vector<int> copies;

	bool* rotate_by_move = new bool(false);
	bool* rotate_by_target = new bool(false);
	bool* wall_mode = new bool(false);
	bool* is_shadow = new bool(false);
	bool* rotate_by_target_gun = new bool(false);

	

	static void clear_default_data(ESprite* _sprite);
	static void set_default_data(ESprite* _sprite);



	ESprite();
	~ESprite();
};

class EItem
{
public:
	EItem();
	~EItem();

	float* item_level = new float(1.0f);

	EGabarite* icon;
};

class EItemAttribute
{
public:
	EItemAttribute();
	~EItemAttribute();

	int* tier = new int(1);
};