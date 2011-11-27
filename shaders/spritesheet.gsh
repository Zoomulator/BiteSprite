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


void GetFrame( usamplerBuffer spriteFrame, uint ID, out vec4 frame, out vec2 anchor );


void main(void)
	{
	fID = gID[0];
	fFlags = gFlags[0];
	fPaletteID = gPaletteID[0];
	bool flipX = bool(gFlags[0] & 4u);
	bool flipY = bool(gFlags[0] & 8u);
	if( bool(gFlags[0] & 1u) ) // is visibility bit set?
		{
		vec4 frame;
		vec2 anchor;
		GetFrame( spriteFrame, gID[0], frame, anchor );
		vec2 size = frame.zw;
		mat4 trans = mat4( 1.0 );
		trans[0].xy = vec2( cos( rot[0]), sin( rot[0] ) ) * scale[0];
		trans[1].xy = vec2( cos( rot[0]+PI/2 ), sin( rot[0]+PI/2 ) ) * scale[0];
		trans[3].xyz = gl_in[0].gl_Position.xyz;

		gl_Position = gl_in[0].gl_Position;
		gl_Position.xy = ceil( vec2(0, size.y) - anchor );
		gl_Position = projection * trans * gl_Position ;
		texCoord = vec2( float(flipX), float(flipY) );
		EmitVertex();
		
		gl_Position = gl_in[0].gl_Position;
		gl_Position.xy = -anchor;
		gl_Position = projection * trans * gl_Position;
		texCoord = vec2( float(flipX), float(!flipY) );
		EmitVertex();

		gl_Position = gl_in[0].gl_Position;
		gl_Position.xy = size - anchor;
		gl_Position = projection * trans * gl_Position;
		texCoord = vec2( float(!flipX), float(flipY) );
		EmitVertex();

		gl_Position = gl_in[0].gl_Position;
		gl_Position.xy = ceil( vec2( size.x, 0) - anchor );
		gl_Position = projection * trans * gl_Position;
		texCoord = vec2( float(!flipX), float(!flipY) );
		EmitVertex();

		EndPrimitive();
		}
	}
	
	

void GetFrame( usamplerBuffer spriteFrame, uint ID, out vec4 frame, out vec2 anchor )
	{
	frame.x = texelFetch( spriteFrame, 6*int(ID) ).r;
	frame.y = texelFetch( spriteFrame, 6*int(ID)+1 ).r;
	frame.z = texelFetch( spriteFrame, 6*int(ID)+2 ).r;
	frame.w = texelFetch( spriteFrame, 6*int(ID)+3 ).r;
	anchor.x = texelFetch( spriteFrame, 6*int(ID)+4 ).r;
	anchor.y = texelFetch( spriteFrame, 6*int(ID)+5 ).r;
	}