

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

float max_color_r;
float max_color_g;
float max_color_b;

float reverse;
void main()
{
	max_color_r = texture(texture1, TexCoord).r;
	max_color_g = texture(texture1, TexCoord).g;
	max_color_b = texture(texture1, TexCoord).b;
	
	max_color_r = max (texture(texture1, TexCoord + vec2(0.003333f, 0.0f)).r, max_color_r);
	if (texture(texture1, TexCoord + vec2(0.003333f, 0.0f)).g > max_color_g) {max_color_g = texture(texture1, TexCoord + vec2(0.003333f, 0.0f)).g;}
	if (texture(texture1, TexCoord + vec2(0.003333f, 0.0f)).b > max_color_b) {max_color_b = texture(texture1, TexCoord + vec2(0.003333f, 0.0f)).b;}
	
	if (texture(texture1, TexCoord + vec2(-0.003333f, 0.0f)).r > max_color_r) {max_color_r = texture(texture1, TexCoord + vec2(-0.003333f, 0.0f)).r;}
	if (texture(texture1, TexCoord + vec2(-0.003333f, 0.0f)).g > max_color_g) {max_color_g = texture(texture1, TexCoord + vec2(-0.003333f, 0.0f)).g;}
	if (texture(texture1, TexCoord + vec2(-0.003333f, 0.0f)).b > max_color_b) {max_color_b = texture(texture1, TexCoord + vec2(-0.003333f, 0.0f)).b;}
	
	if (texture(texture1, TexCoord + vec2(0.0f, 0.003333f)).r > max_color_r) {max_color_r = texture(texture1, TexCoord + vec2(0.0f, 0.003333f)).r;}
	if (texture(texture1, TexCoord + vec2(0.0f, 0.003333f)).g > max_color_g) {max_color_g = texture(texture1, TexCoord + vec2(0.0f, 0.003333f)).g;}
	if (texture(texture1, TexCoord + vec2(0.0f, 0.003333f)).b > max_color_b) {max_color_b = texture(texture1, TexCoord + vec2(0.0f, 0.003333f)).b;}
	
	if (texture(texture1, TexCoord + vec2(0.0f, -0.003333f)).r > max_color_r) {max_color_r = texture(texture1, TexCoord + vec2(0.0f, -0.003333f)).r;}
	if (texture(texture1, TexCoord + vec2(0.0f, -0.003333f)).g > max_color_g) {max_color_g = texture(texture1, TexCoord + vec2(0.0f, -0.003333f)).g;}
	if (texture(texture1, TexCoord + vec2(0.0f, -0.003333f)).b > max_color_b) {max_color_b = texture(texture1, TexCoord + vec2(0.0f, -0.003333f)).b;}
	
	blur2 = (1.0f - blur) / 4.0f;
	reverse = (1.0f - decay_mul);
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor
	=
	clamp 
	(
	(
		(
			(
				vec4 (max_color_r * 0.95f,max_color_g * 0.95f,max_color_b * 0.95f, 1.0f) * decay_mul
				+
				texture(texture1, TexCoord) * reverse
			)
			* blur
			+
			(
				texture(texture1, TexCoord + vec2(0.003333f, 0.0f))
				+
				texture(texture1, TexCoord + vec2(-0.003333f, 0.0f))
				+
				texture(texture1, TexCoord + vec2(0.0f, 0.003333f))
				+
				texture(texture1, TexCoord + vec2(0.0f, -0.003333f))
			) * blur2
		)
	)
	*
	ourColor
	//* vec4(decay_mul,decay_mul,decay_mul,1.0f)
	- vec4(decay_flat,decay_flat,decay_flat,0.0f)
	, 0.0f
	, 100.0f
	) * 1.0f;
	
	//FragColor += vec4(max_color_r, max_color_g, max_color_b, 1.0f) - vec4(0.5f, 0.5f, 0.5f, 0.0f) * ourColor * 0.5f;
	

	//if (FragColor.r <= 0.001f){FragColor.g = 1.0f;}

	
	 //ourColor = clamp(ourColor, 0.0f, 1.0f);
	 //if (ourColor.r < 0.0f) {ourColor.r = 0.0f;} 
	 //if (ourColor.g < 0.0f) {ourColor.g = 0.0f;} 
	 //if (ourColor.b < 0.0f) {ourColor.b = 0.0f;} 
}

