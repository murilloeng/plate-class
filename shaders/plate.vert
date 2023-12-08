#version 330 core

out vec3 out_color;
uniform float size;
uniform vec2 center;
uniform ivec2 screen;
layout (location = 1) in vec3 color;
layout (location = 0) in vec3 position;

vec3 apply_box(vec3 position)
{
	return (position - vec3(center, 0)) / size;
}
vec3 apply_screen(vec3 position)
{
	float w = screen.x;
	float h = screen.y;
	float m = min(w, h);
	position.x = m / w * position.x;
	position.y = m / h * position.y;
	return position;
}

void main(void)
{
	out_color = color;
	gl_Position = vec4(apply_screen(apply_box(position)), 1.0);
}