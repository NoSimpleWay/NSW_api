

#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float blur;
uniform float decay_mul = 1.0f;
uniform float decay_flat = 0.0002f;

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
	* vec4(decay_mul,decay_mul,decay_mul,1.0f)
	- vec4(decay_flat,decay_flat,decay_flat,0.0f)
	, 0.0f
	, 100.0f
	);
	

	//if (FragColor.r <= 0.001f){FragColor.g = 1.0f;}

	
	 //ourColor = clamp(ourColor, 0.0f, 1.0f);
	 //if (ourColor.r < 0.0f) {ourColor.r = 0.0f;} 
	 //if (ourColor.g < 0.0f) {ourColor.g = 0.0f;} 
	 //if (ourColor.b < 0.0f) {ourColor.b = 0.0f;} 
}

