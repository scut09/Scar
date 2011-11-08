uniform sampler2D TextureL0; //rainbow

void main(void) 
{
	vec4 Rrainbow = texture2D( TextureL0, vec2(gl_TexCoord[0]) );

	gl_FragColor = Rrainbow * 0.1;
}