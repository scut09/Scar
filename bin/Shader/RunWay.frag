uniform sampler2D TextureL0;
uniform vec3 ColFrom;
uniform vec3 ColOffset;
uniform float Num;
uniform float TimeMs;
uniform float Begin;

float dua = 500.0;	// 动画持续时间

void main()
{
    if ( TimeMs > Begin )
	{
		vec4 Skin = texture2D( TextureL0, vec2(gl_TexCoord[0]));
		float last = TimeMs - Begin;
		if ( last < dua )
		{
			vec4 Color = vec4( ( ColFrom + ColOffset * Num ) / 255.0, 1.0 );
			float Alpha = last / dua;
			gl_FragColor = Skin * Color * Alpha;
		}
		else
		{
			vec4 Color = vec4( ( ColFrom + ColOffset * Num ) / 255.0, 1.0 );
			gl_FragColor = Skin * Color;
		}
    }
	else
	{
		gl_FragColor = vec4( 0.0 );
	}

} 