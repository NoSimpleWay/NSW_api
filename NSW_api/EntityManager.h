#pragma once

#include <vector>
#include "NSW_api/EGabarite.h"
#include "NSW_api/Batcher.h"
#include "EPath.h"

#include <map>


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

	//bool* inmovable = new bool(false);


	//physical collision gabarite sides
	float* collision_up		= new float(20.0f);
	float* collision_down	= new float(20.0f);
	float* collision_left	= new float(20.0f);
	float* collision_right	= new float(20.0f);

	//path block collision gabarite sides
	float* path_block_gabarite_up = new float(20.0f);
	float* path_block_gabarite_down = new float(20.0f);
	float* path_block_gabarite_left = new float(20.0f);
	float* path_block_gabarite_right = new float(20.0f);

	//shadow block collision gabarite sides
	float* shadow_block_gabarite_up = new float(20.0f);
	float* shadow_block_gabarite_down = new float(20.0f);
	float* shadow_block_gabarite_left = new float(20.0f);
	float* shadow_block_gabarite_right = new float(20.0f);

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

	static void collision_process(Entity* _e, float _d);
	static bool can_see(Entity* _e, Entity* _target, float _d);

	Entity();
	~Entity();

	static std::vector<Entity*> entity_list;


	std::vector <EGabarite*> body;
	std::vector <float> body_offset_x;
	std::vector <float> body_offset_y;

	bool body_rotate_by_move = false;

	bool* controlled_by_ai = new bool (false);
	bool* controlled_by_player = new bool (false);

	std::vector<ESprite*> sprite_list;

	static void draw_sprite(Entity* _e, Batcher* _b, float _d, bool _is_shadow_mode, bool _transparent_is_height);
	//static void draw_shadow_sprite(Entity* _e, Batcher* _b, float _d);

	bool* is_bullet = new bool(false);


	static std::vector <Entity*> entity_collection_list;

	static void update_path_block(Entity* _e);
	static void spread_path_block(Entity* _e);

	bool* have_lifetime = new bool(false);
	float* lifetime = new float(1.0f);


	float* target_vector_x = new float(0.0f);
	float* target_vector_y = new float(0.0f);

	static bool is_collision_left;
	static bool is_collision_right;
	static bool is_collision_up;
	static bool is_collision_down;

	Entity* target;

	float* search_cooldown = new float(0.5f);
	bool* is_see_target = new bool(false);
	float* random_move_timer = new float(0.0f);
	float* random_move_cooldown = new float(0.0f);

	int* random_direction_x = new int(0);
	int* random_direction_y = new int(0);

	int* saved_eb_x = new int(-1);
	int* saved_eb_y = new int(-1);


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

	enum EntityBoolAttributes
	{
		ENTITY_BOOL_ATTRIBUTE_INMOVABLE,
		ENTITY_BOOL_CONTROLLED_BY_AI,
		ENTITY_BOOL_CONTROLLED_BY_PLAYER,
		ENTITY_BOOL_HAVE_LIGHT_SOURCE,
		ENTITY_BOOL_GHOST,
		ENTITY_BOOL_NO_PATH_BLOCK,
		ENTITY_BOOL_NO_LIGHT_BLOCK,


		/*---------DO NOT TOUCH!-----------*/
		/* mark of enum size*/_LAST_ELEMENT_OF_EBA
		/*---------DO NOT TOUCH!-----------*/
	};

	//std::vector <bool> eattr_bool = std::vector<bool>(EntityBoolAttributes::_LAST_ELEMENT_OF_EBA, false);

	static std::vector <int> entity_bool_attribute_id;
	static std::vector < std::string > entity_bool_attribute_names;

	bool* inmovable = new bool(false);
	std::vector <bool*> pointer_to_bool_list = std::vector<bool*>(EntityBoolAttributes::_LAST_ELEMENT_OF_EBA, false);

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

		ENTITY_ATTRIBUTE_SHADOW_TALL,

		ENTITY_ATTRIBUTE_LIGHT_SOURCE_RED,
		ENTITY_ATTRIBUTE_LIGHT_SOURCE_GREEN,
		ENTITY_ATTRIBUTE_LIGHT_SOURCE_BLUE,

		/*---------DO NOT TOUCH!-----------*/
		/* mark of enum size*/_LAST_ELEMENT_OF_EA
		/*---------DO NOT TOUCH!-----------*/
	};

	//static struct attribute_pair
	//{
	static std::vector <int> entity_attribute_id;
	static std::vector < std::string > entity_attribute_names;


	//};






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

	float* mass_pointer;
	float* speed_pointer;
	float* shadow_tall_pointer;
	float* drag_pointer;

	float* light_source_red		= new float(0.0f);
	float* light_source_green	= new float(0.0f);
	float* light_source_blue	= new float(0.0f);

	bool* have_light_source = new bool (false);
	bool* is_ghost = new bool (false);
	bool* no_path_block = new bool (false);
	bool* no_light_block = new bool (false);



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
	static const int CLUSTER_DIM = 60;

	static void put_entity(Entity* _e, float _x, float _y);
	static void put_entity(Entity* _e);

	static ECluster* clusters[CLUSTER_DIM][CLUSTER_DIM];

	bool static collision_left(Entity* _a, Entity* _b);
	bool static collision_right(Entity* _a, Entity* _b);
	bool static collision_down(Entity* _a, Entity* _b);
	bool static collision_up(Entity* _a, Entity* _b);

	bool static collision_left_zero_volume(Entity* _a, Entity* _b);
	bool static collision_right_zero_volume(Entity* _a, Entity* _b);
	bool static collision_down_zero_volume(Entity* _a, Entity* _b);
	bool static collision_up_zero_volume(Entity* _a, Entity* _b);

	int static cluster_on_mouse_x;
	int static cluster_on_mouse_y;

	void static get_cluster_on_mouse_coords();
};

class ESprite
{
public:

	struct sprite_struct
	{
		float* offset_x = new float(0.0f);
		float* offset_y = new float(0.0f);
		float* offset_z = new float(0.0f);

		float* shadow_size_x = new float(1.0f);
		float* shadow_size_y = new float(1.0f);

		float* bottom_tall = new float(1.0f);

		float* shadow_tall = new float(100.0f);
		float* shadow_height = new float(100.0f);

		int* copies = new int(1);

		EGabarite* gabarite = NULL;
		EGabarite* supermap = NULL;
	};

	std::vector <sprite_struct*> sprite_struct_list;

	/*
	std::vector<EGabarite*> gabarite;
	std::vector<EGabarite*> supermap;

	std::vector<float> offset_x;
	std::vector<float> offset_y;
	std::vector<float> offset_z;

	std::vector<int> copies;
	*/

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

	enum ItemAttributeCurrent
	{
		ITEM_ATTRIBUTE_CURRENT_SHOOT_COOLDOWN,
		ITEM_ATTRIBUTE_CURRENT_RELOAD_TIME_PROCESS,

		LAST_ELEMENT_OF_ITEM_CURRENT_ATTRIBUTE
	};

	enum ItemAttribute
	{
		ITEM_ATTRIBUTE_DAMAGE,
		ITEM_ATTRIBUTE_FIRE_DAMAGE,
		ITEM_ATTRIBUTE_COLD_DAMAGE,
		ITEM_ATTRIBUTE_LIGHTNING_DAMAGE,
		ITEM_ATTRIBUTE_BULLET_COUNT,
		ITEM_ATTRIBUTE_ATTACK_COOLDOWN,
		ITEM_ATTRIBUTE_RECOIL,
		ITEM_ATTRIBUTE_AMMO_SIZE,
		ITEM_ATTRIBUTE_RELOAD_TIME,
		ITEM_ATTRIBUTE_ADDED_DAMAGE_MULTIPLIER,
		ITEM_ATTRIBUTE_I,
		ITEM_ATTRIBUTE_J,
		ITEM_ATTRIBUTE_K,


		LAST_ELEMENT_OF_ITEM_ATTRIBUTE
	};

	struct set_affix_base_valuse_struct
	{
		int* id = new int(0);
		float* value = new float(0.0f);

		bool* autopower_by_level = new bool (false);
	};

	std::vector < set_affix_base_valuse_struct*> set_base_value_list;

	struct item_attributes_struct
	{
		float* item_base_attr			= new float(0.0f);
		float* item_increase_attr		= new float(0.0f);
		float* item_more_attr			= new float(0.0f);
		float* item_total_attr			= new float(0.0f);
	}; 

	std::vector <item_attributes_struct*> item_attributes_list = std::vector<item_attributes_struct*>(ItemAttribute::LAST_ELEMENT_OF_ITEM_ATTRIBUTE, new item_attributes_struct);

	enum ItemAttributeCountController
	{
		IACC_TRIGGREABLE_ABILITY,

		LAST_ELEMENT_OF_IACC
	};

	struct iacc_condition_struct
	{
		int* id = new int(0);
		int* more_or_equal = new int(0);
		int* less_or_equal = new int(0);
	};

	struct iacc_struct
	{
		int* id = new int(0);
		int* summator = new int(0);
	};

	struct affix_property
	{
		int* attribute_id = new int(0);//id of attribute

		float* add_base = new float(0.0f);//add or substract
		float* increase = new float(0.0f);//increase or decrease ammount
		float* more = new float(0.0f);//more or less
	};
	/*
	^
	|
	|
	*/
	struct affix_tier_struct//tiers of affix property
	{
		std::vector < affix_property*> affix_property_list;//properties
		float* weight = new float(0.0f);//chance to be chosen
	};
	/*
	^
	|
	|
	*/
	struct affix_struct
	{
		std::string name = "";

		std::vector < affix_tier_struct*> affix_tier_list;//available affixex
		int* selected_tier = new int(0);//selected affix

		std::vector< iacc_struct*> iacc_list;//ban some property tags
		std::vector< iacc_condition_struct*> iacc_condition_list;//banned property cannot be chosed

		float* weight = new float(0.0f);
	};
	/*
	^
	|
	|
	*/
	static std::vector< affix_struct*> AFFIX_REGISTERER;

	std::vector< affix_struct*> generated_affixes_list;
	 
	typedef void (*ITEM_ACTION)(EItem* _item, float _d);

	std::vector<ITEM_ACTION> ITEM_ACTION_ON_SHOOT;
	std::vector<ITEM_ACTION> ITEM_ACTION_ON_USE;

	void static update_item_attributes(EItem* _item);
	//static std::vector<std::s

	EGabarite* icon;
};

class EItemAttribute
{
public:
	EItemAttribute();
	~EItemAttribute();

	int* tier = new int(1);
};