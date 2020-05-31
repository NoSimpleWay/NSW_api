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

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor.rgb
	=
	texture(texture1, TexCoord).rgb
	*
	(
		texture(texture2, TexCoordLightmap).rgb//lightmap
		+
		ambient_color.rgb * (1.0f - texture(texture3, TexCoordShadowmap * vec2(screen_size_x, screen_size_y)).a)//direct light
		+
		texture(texture3, TexCoordShadowmap * vec2(screen_size_x, screen_size_y)).rgb * texture(texture3, TexCoordShadowmap * vec2(screen_size_x, screen_size_y)).a//shadow ambient
	);
	
	//FragColor.r = TexCoordShadowmap.x;
	//FragColor.g = TexCoordShadowmap.y;
	//FragColor.b = 0.0f;
	
	FragColor.a = texture(texture1, TexCoord).a;
}

