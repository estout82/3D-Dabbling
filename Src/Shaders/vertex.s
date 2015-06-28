#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec2 texCoord0;

uniform mat4 worldMatrix;

void main()
{
	texCoord0 = texCoord;
	gl_Position = worldMatrix * vec4(pos, 1.0f);
}