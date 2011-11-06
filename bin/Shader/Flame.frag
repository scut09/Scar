
uniform sampler2D TextureL0; //flame
uniform sampler2D TextureL1; //noise
uniform float TimeMs;

void main()
{
	float t = TimeMs / 500.0;
	vec4 Flame = texture2D( TextureL0, vec2(gl_TexCoord[0]));
	vec4 Noise = texture2D( TextureL1, vec2(gl_TexCoord[0]) + vec2(t/4.0,t));

	gl_FragColor = (Flame * vec4(1,0.8,0.1,0) + Flame.a * vec4(0.8)) * (Noise / 4.0 + 0.75);
}