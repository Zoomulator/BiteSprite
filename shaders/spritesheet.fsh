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

void main(void)
	{
	vec2 sheetSize = textureSize( spriteSheet, 0 );
	vec4 frame = texelFetch( spriteFrame, int(fID) );
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