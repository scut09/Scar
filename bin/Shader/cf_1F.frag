
uniform sampler2D TextureL0; //Diff
uniform sampler2D TextureL1; //Ngs
uniform sampler2D TextureL2; //


varying vec4 LLightInTangentCoord;
varying vec4 HLightInTangentCoord;

void main()
{
	vec4 Skin = texture2D( TextureL0, vec2(gl_TexCoord[0]));
	vec4 Ngs = texture2D( TextureL1, vec2(gl_TexCoord[0]));

	vec3 smoothOut = vec4(0.5, 0.5, 1.0, 1.0);
	float bumpiness = 1.0;

	Ngs = mix( smoothOut, Ngs, bumpiness );

	Ngs = normalize( ( Ngs * 2.0 ) - 1.0 );

	float Light = max( dot(Ngs.agb, LLightInTangentCoord.xyz), 0.0);

	gl_FragColor = Skin * Light;
	gl_FragColor += Skin.a * vec4(2.783133, 4.680723, 7, 1);

} 