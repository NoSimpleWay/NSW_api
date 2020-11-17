

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

float shadow_multiplier;

vec2 shadow_coord;
vec2 light_coord;

float pixel_factor
=
1.0f
/
1580.0f//height of shadowmap
*
256.0f;//gradation of green color

float blur_x_factor = 1.0f / 1920.0f * 1.0f;
float blur_y_factor = 1.0f / 1580.0f;

float bhr1 = 0.0f;
float bhr2 = 0.0f;
float bhr3 = 0.0f;
float bhr4 = 0.0f;
float bhr5 = 0.0f;

float blur_result = 0.0f; 

//vec4 temp_color;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	
	//shadow_coord = vec2(ShadowCoord.x, ShadowCoord.y * (1.0f - texture(texture1, SuperMapCoord).b) + FullShadowCoord * texture(texture1, SuperMapCoord).b - texture(texture1, SuperMapCoord).r * 0.161f) + vec2(offset_x, offset_y);
	
	shadow_coord = vec2(ShadowCoord.x, FullShadowCoord  - texture(texture1, SuperMapCoord).g * pixel_factor + texture(texture1, SuperMapCoord).b * pixel_factor) + vec2(offset_x, offset_y);
	//light_coord = vec2(LightMapCoord.x, FullShadowCoord  - texture(texture1, SuperMapCoord).g * 0.161f + texture(texture1, SuperMapCoord).b * 0.161f) + vec2(offset_x, offset_y);
	
	bhr1 = texture(texture2, shadow_coord + vec2(0.0f, 0.0f)).a;
	bhr2 = texture(texture2, shadow_coord + vec2(blur_x_factor, 0.0f)).a;
	bhr3 = texture(texture2, shadow_coord + vec2(blur_x_factor * 2.0f, 0.0f)).a;
	bhr4 = texture(texture2, shadow_coord + vec2(blur_x_factor * -1.0f, 0.0f)).a;
	bhr5 = texture(texture2, shadow_coord + vec2(blur_x_factor * -2.0f, 0.0f)).a;
	
	blur_result = (bhr1 + bhr2 + bhr3 + bhr4 + bhr5) /5.0f;
	
	shadow_multiplier
	=
	clamp
	(
		(
			texture(texture2, shadow_coord).a //0.21
			//blur_result
			-
			texture(texture1, SuperMapCoord).g// 0.43
			-
			ShadowCoord.y / 255.0f
		)
		*
		10.0f
		,
		0.0f
		,
		1.0f
	)*blur_result;
	//*
	//texture(texture2, shadow_coord).a
	;
	
	
	
	FragColor.rgb
	=
	texture(texture1, TexCoord).rgb
	*
	(
		(
			shadow_multiplier * texture(texture2, shadow_coord).rgb
		)
		+
		(
			(1.0f - shadow_multiplier) * ourColor.rgb
		)
		+
		(texture(texture3, LightMapCoord).rgb * (1.0f - texture(texture1, SuperMapCoord).g) * (1.0f - texture(texture1, SuperMapCoord).g))
	)

	;
	
	//FragColor.rgb = vec3(FullShadowCoord + offset_y);
	
	FragColor.a = texture(texture1, TexCoord).a * ourColor.a;
}

