#version 400

in vec3 vp;
out vec3 color;

uniform mat4 MVP;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj; 

void main()
{
	gl_Position = proj * view * model * vec4(vp, 1.0); 
}