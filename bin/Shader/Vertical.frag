uniform sampler2D TextureL0;
uniform sampler2D TextureL1;

varying float offset;

void main()
{
    vec4 Skin = texture2D( TextureL0, (vec2(gl_TexCoord[0]) + vec2(0, offset) - vec2(0, 0.5)) * vec2( 1.0, 0.5 ));
	vec4 Alpha = texture2D( TextureL1, vec2(gl_TexCoord[0]) );
	gl_FragColor = Skin * Alpha;
} 