uniform sampler2D TextureL0;

void main()
{
	vec4 Skin = texture2D( TextureL0, vec2(gl_TexCoord[0]));

	gl_FragColor = Skin * vec4( 1, 1, 0, 1 );
	//gl_FragColor += vec4(Skin.a) * vec4(2.783133, 4.680723, 7, 1);

} 