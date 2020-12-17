#version 330 core
in vec2 TexCoord;
in vec2 TexCoordLightmap;
in vec2 TexCoordShadowmap;
out vec4 FragColor;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform vec4 ambient_color;

uniform float screen_size_x;
uniform float screen_size_y;

uniform float gamma_factor = 0.1f;
uniform float gamma_offset = 1.0f;
uniform float gamma_border = 4.0f;

vec3 result_pixel;

float gamma_R = 1.0;
float gamma_G = 1.0;
float gamma_B = 1.0;
void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	

	result_pixel = texture(texture1, TexCoord).rgb
					*
					(
						texture(texture2, TexCoordLightmap).rgb//lightmap
						+
						ambient_color.rgb * (1.0f - texture(texture3, TexCoordShadowmap * vec2(screen_size_x, screen_size_y)).a)//direct light
						+
						texture(texture3, TexCoordShadowmap * vec2(screen_size_x, screen_size_y)).rgb * texture(texture3, TexCoordShadowmap * vec2(screen_size_x, screen_size_y)).a//shadow ambient
					);
					
	/*gamma_R = clamp (sin((pow(result_pixel.r, gamma_offset) * gamma_border - gamma_border/2.0f) * 1.5705f) * gamma_factor + 1.0f, 0.0f, 2.0f);
	gamma_G = clamp (sin((pow(result_pixel.g, gamma_offset) * gamma_border - gamma_border/2.0f) * 1.5705f) * gamma_factor + 1.0f, 0.0f, 2.0f);
	gamma_B = clamp (sin((pow(result_pixel.b, gamma_offset) * gamma_border - gamma_border/2.0f) * 1.5705f) * gamma_factor + 1.0f, 0.0f, 2.0f);*/
	
	FragColor.rgb
	=
	result_pixel * vec3(gamma_R, gamma_G, gamma_B);
	
	//FragColor.rgb = vec3(pow(result_pixel.rgb, vec3(2.0f)));
	
	/*FragColor.rgb
	=
	vec3
	(
		sin
		(
			(pow (result_pixel, vec3(gamma_offset)) * 4.0f - 2.0f) * 1.5705f
		)
		* gamma_factor + 1.0f
	)
	*
	result_pixel;*/
	FragColor.rgb = vec3(pow(result_pixel, vec3(pow(0.5f + result_pixel, vec3(-gamma_factor)))));
	//*
	//vec3(0.9f,0.95f,1.0f);
	

	//FragColor.r = TexCoordShadowmap.x;
	//FragColor.g = TexCoordShadowmap.y;
	//FragColor.b = 0.0f;
	
	FragColor.a = texture(texture1, TexCoord).a;
}

