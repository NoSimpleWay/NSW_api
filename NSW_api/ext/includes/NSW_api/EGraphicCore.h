#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EGabarite.h"

#include <stb_image.h>
#include <learnopengl/shader_s.h>
#include "Batcher.h"
#include "EGabarite.h"
#include <vector>

class EGraphicCore {
public:
	static unsigned char* data1;
	static unsigned int texture[32];
	static int width, height, nrChannels;

	static int last_texture_w;
	static int last_texture_h;

	static Shader* ourShader;
	static Shader* shadowmap;
	static Shader* shader_terrain;
	static Shader* lightmap_blur;
	static Shader* lightmap_spread;

	static Batcher* batch;
	static Batcher* batch_shadowmap;
	static Batcher* batch_terrain;

	static glm::mat4 matrix_transform;

	static int SCR_WIDTH;
	static int SCR_HEIGHT;

	static float correction_x;
	static float correction_y;

	static void load_texture(char const* _path, int _id);

	static std::vector<EGabarite*> gabarite_list;
	//static std::vector<EGabarite*> gabarite_collection;

	static EGabarite* gabarite_white_pixel;
	static EGabarite* gabarite_tileset;
	static EGabarite* gabarite_small_wood_button_bg;
	static EGabarite* gabarite_wood_button_bg;
	static EGabarite* gabarite_ERROR;

	EGraphicCore();
	~EGraphicCore();
};