

#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;
in vec2 ShadowCoord;
in vec2 SuperMapCoord;
in vec2 LightMapCoord;
in float FullShadowCoord;

// texture samplers
uniform sampler2D texture1;//normal texture and supermap texture
uniform sampler2D texture2;//shadowmap
uniform sampler2D texture3;//lightmap

uniform float offset_x;
uniform float offset_y;

uniform float screen_size_x;
uniform float screen_size_y;

uniform vec4 ambient_light_color;

uniform float zoom;

uniform float gamma_factor = 0.1f;
uniform float gamma_offset = 1.0f;
uniform float gamma_border = 4.0f;

float shadow_multiplier;

vec2 shadow_coord;
vec2 light_coord;

float pixel_factor
=
1.0f
/
1580.0f//height of shadowmap
*
255.0f;//gradation of green color

float pixel_factor_for_lightmap
=
1.0f
/
12000.0f//height of shadowmap
*
256.0f;//gradation of green color

float blur_x_factor = 1.0f / 1920.0f * 1.0f;
float blur_y_factor = 1.0f / 1580.0f;

float bhr1 = 0.0f;
float bhr2 = 0.0f;
float bhr3 = 0.0f;
float bhr4 = 0.0f;
float bhr5 = 0.0f;

float blur_result1 = 0.0f; 
float blur_result2 = 0.0f; 
float blur_result3 = 0.0f; 
float blur_result4 = 0.0f; 
float blur_result5 = 0.0f; 

float blur_total = 0.0f; 

float halt = 0.0f;
float light_halt = 0.0f;

float normal_y = 0.0f;

in float camera_x;
in float camera_y;

vec3 texture_pixel;
vec3 shadow_pixel;
vec3 ambient_pixel;
vec3 recolor;
vec3 lightmap_pixel;
//vec4 temp_color;
vec3 result_pixel;

float gamma_R = 1.0;
float gamma_G = 1.0;
float gamma_B = 1.0;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	
	//shadow_coord = vec2(ShadowCoord.x, ShadowCoord.y * (1.0f - texture(texture1, SuperMapCoord).b) + FullShadowCoord * texture(texture1, SuperMapCoord).b - texture(texture1, SuperMapCoord).r * 0.161f) + vec2(offset_x, offset_y);
	
	shadow_coord
	=
	vec2
	(
		ShadowCoord.x,
		
		FullShadowCoord
		+ texture(texture1,SuperMapCoord).g
		* 1.0f * zoom * pixel_factor * 1.0f
		+ texture(texture1,SuperMapCoord).b
		* 1.0f * zoom * pixel_factor * 1.0f			
	)
	+
	(	vec2(offset_x, offset_y)	);/*camera offset*/
	
	light_coord
	=
	vec2
	(
		LightMapCoord.x,
		
		LightMapCoord.y
		+ texture(texture1,SuperMapCoord).b
		* 1.0f * zoom * pixel_factor_for_lightmap * 1.0f		
		+ texture(texture1,SuperMapCoord).g
		* 1.0f * zoom * pixel_factor_for_lightmap * 1.0f			
	);
	//light_coord = vec2(LightMapCoord.x, FullShadowCoord  - texture(texture1, SuperMapCoord).g * 0.161f + texture(texture1, SuperMapCoord).b * 0.161f) + vec2(offset_x, offset_y);
	
	
	/*blur*/
	bhr1 = clamp (texture(texture2, shadow_coord + vec2(0.0f					, 0.0f)).a * 200.0f, 0.0f, 1.0f);
	bhr2 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * 1.0f	, 0.0f)).a * 200.0f, 0.0f, 1.0f);
	bhr3 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * 2.0f	, 0.0f)).a * 200.0f, 0.0f, 1.0f);
	bhr4 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * -1.0f	, 0.0f)).a * 200.0f, 0.0f, 1.0f);
	bhr5 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * -2.0f	, 0.0f)).a * 200.0f, 0.0f, 1.0f);
	blur_result1 = (bhr1 + bhr2 + bhr3 + bhr4 + bhr5) / 5.0f;
	
	bhr1 = clamp (texture(texture2, shadow_coord + vec2(0.0f,						blur_y_factor * -1.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr2 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * 1.0f,		blur_y_factor * -1.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr3 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * 2.0f,		blur_y_factor * -1.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr4 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * -1.0f,		blur_y_factor * -1.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr5 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * -2.0f,		blur_y_factor * -1.0f)).a * 20.0f, 0.0f, 1.0f);
	blur_result2 = (bhr1 + bhr2 + bhr3 + bhr4 + bhr5) / 5.0f;
	
	bhr1 = clamp (texture(texture2, shadow_coord + vec2(0.0f,						blur_y_factor * -2.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr2 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * 1.0f,		blur_y_factor * -2.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr3 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * 2.0f,		blur_y_factor * -2.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr4 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * -1.0f,		blur_y_factor * -2.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr5 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * -2.0f,		blur_y_factor * -2.0f)).a * 20.0f, 0.0f, 1.0f);
	blur_result3 = (bhr1 + bhr2 + bhr3 + bhr4 + bhr5) / 5.0f;
	
	bhr1 = clamp (texture(texture2, shadow_coord + vec2(0.0f,						blur_y_factor * 1.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr2 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * 1.0f,		blur_y_factor * 1.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr3 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * 2.0f,		blur_y_factor * 1.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr4 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * -1.0f,		blur_y_factor * 1.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr5 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * -2.0f,		blur_y_factor * 1.0f)).a * 20.0f, 0.0f, 1.0f);
	blur_result4 = (bhr1 + bhr2 + bhr3 + bhr4 + bhr5) / 5.0f;
	
	bhr1 = clamp (texture(texture2, shadow_coord + vec2(0.0f,						blur_y_factor * 2.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr2 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * 1.0f,		blur_y_factor * 2.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr3 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * 2.0f,		blur_y_factor * 2.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr4 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * -1.0f,		blur_y_factor * 2.0f)).a * 20.0f, 0.0f, 1.0f);
	bhr5 = clamp (texture(texture2, shadow_coord + vec2(blur_x_factor * -2.0f,		blur_y_factor * 2.0f)).a * 20.0f, 0.0f, 1.0f);
	blur_result5 = (bhr1 + bhr2 + bhr3 + bhr4 + bhr5) / 5.0f;
	
	blur_total = (blur_result1 + blur_result2 + blur_result3 + blur_result4 + blur_result5) / 5.0f;
	
	//									0.7803						0.23
	//halt = texture(texture1,SuperMapCoord).g * 1.0f * zoom * 1.0f/screen_size_y * 255.0f * 1.0f;
	//halt = ShadowCoord.y / screen_size_y;
	
	halt = ShadowCoord.y / screen_size_y - texture(texture1,SuperMapCoord).g * zoom * 1.0f/screen_size_y * 255.0f;
	//normal_y = texture(texture1,SuperMapCoord).g - texture(texture1,SuperMapCoord - vec2(0.0f, 0,00024414.0f).g
	//halt = 1.0f;
	
	//light_halt = LightMapCoord.y;
	
	shadow_multiplier
	=
	clamp
	(
		(
		
			texture(texture2, shadow_coord).a
			-
			halt * 1.0f
	
		)
		*
		64.0f
		,
		0.0f
		,
		1.0f
	)*blur_total;
	
	//blur_result
	//*
	//texture(texture2, shadow_coord).a
	;
	
	
	texture_pixel = texture(texture1, TexCoord).rgb;
	shadow_pixel = shadow_multiplier * texture(texture2, shadow_coord).rgb;
	ambient_pixel = (1.0f - shadow_multiplier) * ambient_light_color.rgb;
	recolor = ourColor.rgb * vec3(2.0f, 2.0f, 2.0f);
	lightmap_pixel = texture(texture3, light_coord).rgb / (1.0f + halt * halt * 32.0f);
	
	result_pixel = texture_pixel * ((shadow_pixel + ambient_pixel) * recolor + lightmap_pixel);
	
	gamma_R = sin((pow(result_pixel.r, gamma_offset) * gamma_border - gamma_border / 2.0f) * 1.5705f) * gamma_factor + 1.0f;
	gamma_G = sin((pow(result_pixel.g, gamma_offset) * gamma_border - gamma_border / 2.0f) * 1.5705f) * gamma_factor + 1.0f;
	gamma_B = sin((pow(result_pixel.b, gamma_offset) * gamma_border - gamma_border / 2.0f) * 1.5705f) * gamma_factor + 1.0f;
	
	FragColor.rgb =	clamp(result_pixel * vec3(gamma_R, gamma_G, gamma_B), vec3(0.0f), vec3(1.0f));//vec3 (( sin (() * 4.0f - 2.0f) * 1.5705f) / 10.0f + 1.0f);
	//FragColor.rgb = vec3(pow(result_pixel, vec3(pow(0.5f + result_pixel, vec3(-gamma_factor)))));
		
	//FragColor.rgb = 

	//FragColor.rgb =	vec3(pow(result_pixel, 1.1f));
	
	/*FragColor.r = halt;
	FragColor.g = 0.0f;
	FragColor.b = 0.0f;*/
	
	FragColor.a = texture(texture1, TexCoord).a * ourColor.a;
	
	//FragColor.rgb = vec3(ShadowCoord.y / screen_size_y);	
	//FragColor.a = 1.0f;	
}

