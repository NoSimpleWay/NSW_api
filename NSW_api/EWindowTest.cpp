#include "EWindowTest.h"
#include "Entity.h"

int native_copper = 1;
int poor_copper = 1;
int normal_copper = 1;
int rich_copper = 1;
int ingot_copper = 1;

int native_sphalerite = 1;
int poor_sphalerite = 1;
int normal_sphalerite = 1;
int rich_sphalerite = 1;
int ingot_sphalerite = 1;

int native_vismut = 1;
int poor_vismut = 1;
int normal_vismut = 1;
int rich_vismut = 1;
int ingot_vismut = 1;


float summary_alloy = 0;

float min_copper = 0.5f;
float max_copper = 0.65f;

float min_sphalerite = 0.20f;
float max_sphalerite = 0.30f;

float min_vismut = 0.10f;
float max_vismut = 0.20f;

std::string s;

int maximum_alloy = 0;

EWindowTest::EWindowTest()
{
	//std::cout << "Ceil(0.001) = " << ceil(0.001f) << std::endl;
	for (int i = 0; i < 10; i++)
	{
		Entity* en = new Entity();

		Entity::entity_list.push_back(en);
		*en->position_x = (float) (rand() % 500) + 20.0f;
		*en->position_y = (float) (rand() % 500) + 20.0f;
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
}

void EWindowTest::default_draw(float _d)
{
}

void EWindowTest::draw(float _d)
{
	EGraphicCore::batch->setcolor(EColor::COLOR_RED);

	for (Entity* e : Entity::entity_list)
	{
		EGraphicCore::batch->draw_gabarite(*e->position_x - 10.0f, *e->position_y - 10.0f, 20.0f, 20.0f, EGraphicCore::gabarite_white_pixel);
	}

	/*EGraphicCore::batch->setcolor(EColor::COLOR_BLACK);
	EGraphicCore::batch->draw_gabarite(100.0f + rand() % 10, 200.0f, 512.0f, 64.0f, EGraphicCore::gabarite_white_pixel);*/
}

void EWindowTest::draw_interface(float _d)
{
}
