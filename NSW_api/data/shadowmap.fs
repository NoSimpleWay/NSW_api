

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

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	
	shadow_coord = vec2(ShadowCoord.x, ShadowCoord.y * (1.0f - texture(texture1, SuperMapCoord).b) + FullShadowCoord * texture(texture1, SuperMapCoord).b) + vec2(offset_x, offset_y);
	
	shadow_multiplier
	=
	clamp
	(
		(
			texture(texture2, shadow_coord).a //0.21
			-
			texture(texture1, SuperMapCoord).g// 0.43
		)
		*
		10.0f
		,
		0.0f
		,
		1.0f
	)
	*
	texture(texture2, shadow_coord).a
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
		(texture(texture3, LightMapCoord).rgb * (1.0f - texture(texture1, SuperMapCoord).g))
	)

	;
	
	//FragColor.rgb = vec3(FullShadowCoord + offset_y);
	
	FragColor.a = texture(texture1, TexCoord).a * ourColor.a;
}

