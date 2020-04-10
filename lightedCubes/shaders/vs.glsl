#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 normal; 
layout (location = 2) in vec2 texuv; 

out vec3 fragPos; 
out vec3 Normal; 
out vec2 uv; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj; 
uniform int index;  

void main()
{
	gl_Position = proj * view * model * vec4(vp, 1.0);
	fragPos = vec3(model * vec4(vp, 1.0f));
	Normal = mat3(transpose(inverse(model))) * normal;  
	uv = texuv; 
}