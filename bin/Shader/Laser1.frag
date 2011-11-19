uniform sampler2D TextureL0;

void main()
{	
	vec4 Skin = texture2D( TextureL0, vec2(gl_TexCoord[0] ) );
	gl_FragColor = Skin * vec4( 1, 1, 0, 1 );
}