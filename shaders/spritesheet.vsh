#version 330

uniform sampler2D spriteSheet;
uniform usamplerBuffer spriteFrame;
uniform mat4 projection;
uniform mat4 view;

in vec4 vertex;
in vec2 rotscale;
in uint templateID;
in uint flags;

out uint gID;
out uint gFlags;
out float rot;
out float scale;

void main(void)
	{
	gID = templateID;
	gFlags = flags;
	rot = radians(rotscale.x);
	scale = rotscale.y;
	gl_Position = ivec4(vertex);
	gl_Position.w = 1;
	}