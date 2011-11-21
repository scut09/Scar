uniform sampler2D TextureL0;

void main()
{
	vec4 flare = texture2D( TextureL0, vec2(gl_TexCoord[0]) );
	gl_FragColor = flare;
}