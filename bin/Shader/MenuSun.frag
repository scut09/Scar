uniform sampler2D TextureL0; //Sun

void main(void) 
{
	vec4 Sun = texture2D( TextureL0, vec2(gl_TexCoord[0]) );

	gl_FragColor = Sun * 1.2;
}