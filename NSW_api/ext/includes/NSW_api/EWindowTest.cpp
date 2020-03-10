#include "EWindowTest.h"

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

	std::cout << std::endl;

	for (int nc = 0; nc <=native_copper; nc++)
	for (int pc = 0; pc <=poor_copper; pc++)
	for (int noc = 0; noc <=normal_copper; noc++)
	for (int rc = 0; rc <=rich_copper; rc++)

	for (int ns = 0; ns <=native_sphalerite; ns++)
	for (int ps = 0; ps <=poor_sphalerite; ps++)
	for (int nos = 0; nos <=normal_sphalerite; nos++)
	for (int rs = 0; rs <=rich_sphalerite; rs++)

	for (int nv = 0; nv <=native_vismut; nv++)
	for (int pv = 0; pv <=poor_vismut; pv++)
	for (int nov = 0; nov <=normal_vismut; nov++)
	for (int rv = 0; rv <= rich_vismut; rv++)
	{
		int total_copper =		nc * 10.0f + pc * 15.0f + noc * 25.0f + rc * 35.0f;
		int total_sphalerite =	ns * 10.0f + ps * 15.0f + nos * 25.0f + rs * 35.0f;
		int total_vismut =		nv * 10.0f + pv * 15.0f + nov * 25.0f + rv * 35.0f;

		summary_alloy = total_copper + total_sphalerite + total_vismut;

		int slot = 0;

		slot += ceil(nc / 16.0f) + ceil(pc / 16.0f) + ceil(noc / 16.0f) + ceil(rc / 16.0f);
		slot += ceil(ns / 16.0f) + ceil(ps / 16.0f) + ceil(nos / 16.0f) + ceil(rs / 16.0f);
		slot += ceil(nv / 16.0f) + ceil(pv / 16.0f) + ceil(nov / 16.0f) + ceil(rv / 16.0f);
		//if (native_copper > 0) { slot}

		if ((summary_alloy > 0) && (slot <= 4) && ((int)(summary_alloy/100.0f) * 100 == summary_alloy) && (summary_alloy > maximum_alloy))
		{
			if 
			(
				(total_copper/summary_alloy >= min_copper)&&(total_copper / summary_alloy <= max_copper)
				&&
				(total_sphalerite /summary_alloy >= min_sphalerite)&&(total_sphalerite / summary_alloy <= max_sphalerite)
				&&
				(total_vismut / summary_alloy >= min_vismut) && (total_vismut / summary_alloy <= max_vismut)
				
			)
			{
				maximum_alloy = summary_alloy;
				std::cout << "Total: " << summary_alloy << " copper: " << (round(total_copper / summary_alloy * 100.0f)) << "% zink: " << round(total_sphalerite / summary_alloy*100.0f) << "% bismuth: " << round(total_vismut / summary_alloy*100.0f) << "%" << std::endl ;
				
				if (nc > 0) { std::cout << "Native copper: " << nc << std::endl; }
				if (pc > 0) { std::cout << "Poor copper: " << pc << std::endl; }
				if (noc > 0) { std::cout << "Normal copper: " << noc << std::endl; }
				if (rc > 0) { std::cout << "Rich copper: " << rc << std::endl; }

				if (ns > 0) { std::cout << "Native sphalerite: " << ns << std::endl; }
				if (ps > 0) { std::cout << "Poor sphalerite: " << ps << std::endl; }
				if (nos > 0) { std::cout << "Normal sphalerite: " << nos << std::endl; }
				if (rs > 0) { std::cout << "Rich sphalerite: " << rs << std::endl; }

				if (nv > 0) { std::cout << "Native bismuth: " << nv << std::endl; }
				if (pv > 0) { std::cout << "Poor bismuth: " << pv << std::endl; }
				if (nov > 0) { std::cout << "Normal bismuth: " << nov << std::endl; }
				if (rv > 0) { std::cout << "Rich bismuth: " << rv << std::endl; }

				std::cout << std::endl;
				//if ()
			}
			else
			{
				//std::cout << "FAIL: " << summary_alloy << " copper: " << (total_copper / summary_alloy) << "% zink: " << total_sphalerite / summary_alloy << " copper: " << total_vismut / summary_alloy << std::endl;
			}
			
		}
	}

	EButton* but = new EButton(0.0f, 0.0f, 100.0f, 20.0f);
	but->master_window = this;
	but->have_input_mode = true;
	but->master_position = Enums::PositionMaster::WINDOW;

	button_list.push_back(but);
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
	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1, -1, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x, EGraphicCore::correction_y, 1));

	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	EGraphicCore::batch->setcolor(EColor::COLOR_BLACK);
	EGraphicCore::batch->draw_gabarite(100.0f + rand() % 10, 200.0f, 512.0f, 64.0f, EGraphicCore::gabarite_white_pixel);
}

void EWindowTest::draw_interface(float _d)
{
}
