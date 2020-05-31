

#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor
	=
	clamp
	(
		texture(texture1, TexCoord)
		+
		texture(texture1, TexCoord + vec2(0.003333f, 0.0f))
		+
		texture(texture1, TexCoord + vec2(-0.003333f, 0.0f))
		+
		texture(texture1, TexCoord + vec2(0.0f, 0.003333f))
		+
		texture(texture1, TexCoord + vec2(0.0f, -0.003333f))
		,
		0.0f,
		1.0f
		
	)
	*
	ourColor;
}

