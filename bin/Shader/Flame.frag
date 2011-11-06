
uniform sampler2D TextureL0; //flame
uniform sampler2D TextureL1; //noise
uniform float TimeMs;
uniform vec3 LoColor;
uniform vec3 HiColor;

void main()
{
	float t = TimeMs / 500.0;
	vec4 Flame = texture2D( TextureL0, vec2(gl_TexCoord[0]));
	vec4 Noise = texture2D( TextureL1, vec2(gl_TexCoord[0]) + vec2(t/4.0,t));

	gl_FragColor = (Flame * vec4(LoColor, 0) + Flame.a * vec4(HiColor, 0)) * (Noise / 4.0 + 0.75);
}