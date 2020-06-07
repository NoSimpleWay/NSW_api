

#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float blur;

float blur2;


void main()
{
	blur2 = (1.0f - blur) / 4.0f;
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor
	=
	clamp 
	(
	(
		(
			texture(texture1, TexCoord) * blur
			+
			texture(texture1, TexCoord + vec2(0.003333f, 0.0f)) * blur2
			+
			texture(texture1, TexCoord + vec2(-0.003333f, 0.0f)) * blur2
			+
			texture(texture1, TexCoord + vec2(0.0f, 0.003333f)) * blur2
			+
			texture(texture1, TexCoord + vec2(0.0f, -0.003333f)) * blur2
		)
	)
	*
	ourColor
	* vec4(0.99f,0.99f,0.99f,1.0f)
	- vec4(0.002f,0.002f,0.002f,0.0f)
	, 0.0f
	, 100.0f
	);
}

