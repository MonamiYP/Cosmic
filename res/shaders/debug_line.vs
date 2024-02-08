#version 330

uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

layout (location = 0) in vec3 pos;

void main(void) 
{
	gl_Position = u_projection * u_view * u_model * vec4(pos, 1.0);
}