#version 330
		
layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 4) out;
const float PI = 3.141592653589793;

in uint gID[];
in uint gFlags[];
in float rot[];
in float scale[];
in uint gPaletteID[];
flat out uint fID;
flat out uint fFlags;
flat out uint fPaletteID;
smooth out vec2 texCoord;

uniform usamplerBuffer spriteFrame;
uniform mat4 projection;
uniform mat4 view;

void main(void)
	{
	fID = gID[0];
	fFlags = gFlags[0];
	fPaletteID = gPaletteID[0];
	if( bool(gFlags[0] & 1u) ) // is visibility bit set?
		{
		vec4 frame = texelFetch( spriteFrame, int(gID[0]) );
		vec2 size = frame.zw;
		mat4 trans = mat4( 1.0 );
		trans[0].xy = vec2( cos( rot[0]), sin( rot[0] ) ) * scale[0];
		trans[1].xy = vec2( cos( rot[0]+PI/2 ), sin( rot[0]+PI/2 ) ) * scale[0];
		trans[3].xyz = gl_in[0].gl_Position.xyz;

		gl_Position = gl_in[0].gl_Position;
		gl_Position.xy = ceil( vec2(-size.x / 2, size.y / 2) );
		gl_Position = projection * trans * gl_Position ;
		texCoord = vec2( 0, 0 );
		EmitVertex();
		
		gl_Position = gl_in[0].gl_Position;
		gl_Position.xy = ceil(-size/2);
		gl_Position = projection * trans * gl_Position;
		texCoord = vec2( 0, 1 );
		EmitVertex();

		gl_Position = gl_in[0].gl_Position;
		gl_Position.xy = ceil(size/2);
		gl_Position = projection * trans * gl_Position;
		texCoord = vec2( 1, 0 );
		EmitVertex();

		gl_Position = gl_in[0].gl_Position;
		gl_Position.xy = ceil( vec2( size.x/2, -size.y/2) );
		gl_Position = projection * trans * gl_Position;
		texCoord = vec2( 1, 1 );
		EmitVertex();

		EndPrimitive();
		}
	}