#version 400

layout (location = 0) in vec2 vp;
layout (location = 1) in vec2 screenTexCoords;

out vec2 texCoords;

void main()
{
	texCoords = screenTexCoords;
	gl_Position = vec4(vp.x, vp.y, 0.0, 1.0); 
}