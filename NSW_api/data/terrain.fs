#version 330 core
in vec2 TexCoord;
in vec2 TexCoordLightmap;
out vec4 FragColor;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec4 ambient_color;


void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = texture(texture1, TexCoord) * (texture(texture2, TexCoordLightmap) + ambient_color);
}

