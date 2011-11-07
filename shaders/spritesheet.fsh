#version 330

uniform sampler2D spriteSheet;
uniform usamplerBuffer spriteFrame;
uniform mat4 projection;
uniform mat4 view;
uniform vec4 colorKey;

flat in uint fID;
flat in uint fFlags;
in vec2 texCoord;
out vec4 fragColor;

void main(void)
	{
	vec2 sheetSize = textureSize( spriteSheet, 0 );
	vec4 frame = texelFetch( spriteFrame, int(fID) );
	vec2 spriteCoord = (frame.xy + texCoord * frame.zw) / sheetSize;

	fragColor = texelFetch( spriteSheet, ivec2( spriteCoord * sheetSize ), 0 );
	if( bool(fFlags & 2u) &&
		all( lessThan(colorKey.rgb-colorKey.a, fragColor.rgb) &&
		lessThan(fragColor.rgb, colorKey.rgb+colorKey.a) )  ) discard;
	}