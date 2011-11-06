
uniform sampler2D TextureL0; //flame

void main()
{
	
	vec4 Flame = texture2D( TextureL0, vec2(gl_TexCoord[0]));

	gl_FragColor = Flame * vec4(1,0.8,0.1,0) + Flame.a * vec4(0.8);
}