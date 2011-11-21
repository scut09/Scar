uniform sampler2D TextureL0;
varying float a;

void main()
{
	vec4 flare = texture2D( TextureL0, vec2(gl_TexCoord[0]) );
	gl_FragColor = flare * vec4( 1.0, 0.8, 0.7, 1.0 ) * vec4( a );
	//gl_FragColor = flare * vec4( 1.0, 0.8, 0.7, 1.0 );
}