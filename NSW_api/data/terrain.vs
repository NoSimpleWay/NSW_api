#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out vec2 TexCoordLightmap;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	TexCoordLightmap = vec2(aPos.x / 12000.0f, aPos.y / 12000.0f);
}