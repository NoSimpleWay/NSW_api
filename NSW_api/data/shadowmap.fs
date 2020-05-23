

#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;
in vec2 ShadowCoord;
in vec2 SuperMapCoord;

// texture samplers
uniform sampler2D texture1;//normal texture and supermap texture
uniform sampler2D texture2;//shadowmap

uniform float offset_x;
uniform float offset_y;

float shadow_multiplier;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	
	
	shadow_multiplier
	=
	clamp
	(
		(
			texture(texture2, ShadowCoord + vec2(offset_x, offset_y)).a //0.21
			-
			texture(texture1, SuperMapCoord).g// 0.43
		)
		*
		5.0f
		,
		0.0f
		,
		1.0f
	);
	
	FragColor.rgb
	=
	texture(texture1, TexCoord).rgb
	*
	(
		(1.0f - shadow_multiplier)
		+
		texture(texture2, ShadowCoord + vec2(offset_x, offset_y)).rgb * shadow_multiplier
	)
	*
	ourColor.rgb;
	
	//FragColor.rgb = texture(texture1, SuperMapCoord).rgb;
	
	FragColor.a = texture(texture1, TexCoord).a * ourColor.a;
}

