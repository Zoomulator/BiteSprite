#version 330

uniform sampler2D spriteSheet;
uniform usamplerBuffer spriteFrame;
uniform usamplerBuffer palette;
uniform mat4 projection;
uniform mat4 view;
uniform vec4 colorKey;
uniform uint usePalette;

flat in uint fID;
flat in uint fFlags;
flat in uint fPaletteID;
in vec2 texCoord;
out vec4 fragColor;

const uint palSize = 256u;

void GetFrame( usamplerBuffer spriteFrame, uint ID, out vec4 frame, out vec2 anchor );
	
	
void main(void)
	{
	vec2 sheetSize = textureSize( spriteSheet, 0 );
	vec4 frame;
	vec2 anchor;
	
	GetFrame( spriteFrame, fID, frame, anchor );
	
	vec2 spriteCoord = (frame.xy + texCoord * frame.zw) / sheetSize;
	
	if( usePalette == 1u )
		{
		uint palOffset = fPaletteID * 256u;
		float val = texelFetch( spriteSheet, ivec2( spriteCoord * sheetSize ), 0 ).r;
		fragColor = vec4(
			texelFetch( palette, int(palOffset + val*palSize) ) ) / vec4(float(palSize));
		}
	else
		{
		fragColor = texelFetch( spriteSheet, ivec2( spriteCoord * sheetSize ), 0 );
		}	
	
	// Colorkey check
	if( bool(fFlags & 2u) &&
		all( lessThan(colorKey.rgb-colorKey.a, fragColor.rgb) &&
			lessThan(fragColor.rgb, colorKey.rgb+colorKey.a) )  )
		{
		discard;
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
