
uniform sampler2D TextureL0; //
uniform sampler2D TextureL1; //Dense
uniform sampler2D TextureL2; //Cloud
uniform sampler2D TextureL3; //CitiLight
uniform float TimeMs;

varying vec4 DiffLight;
varying vec4 AmbiLight;
varying vec4 Light;

void main(void) 
{
	float t = TimeMs / 500000.0;
	vec4 GroundColor = texture2D( TextureL0, vec2(gl_TexCoord[0]) );
	vec4 DenseColor = texture2D( TextureL1, vec2(gl_TexCoord[0]) );
	vec4 CloudColor = texture2D( TextureL2, vec2(gl_TexCoord[0]) + vec2(t,0) );
	vec4 CityLight = texture2D( TextureL3, vec2(gl_TexCoord[0]) );

	//CloudColor = CloudColor * 0.4;
	CloudColor = vec4( (CloudColor.rbg * CloudColor.a), 1.0 );
	GroundColor = vec4( (GroundColor.rbg * GroundColor.a), 1.0 );

	//gl_FragColor = GroundColor * vec4( 0.8, 0.85, 1.0, 1.0 );
	gl_FragColor = DenseColor * vec4( 0.85, 0.9, 1.0, 1.0 );
	gl_FragColor += GroundColor;
	gl_FragColor += CloudColor * 0.8;
	gl_FragColor *= Light * 1.6;
	gl_FragColor += (1 - Light) * vec4(CityLight.r) * 2;
	//gl_FragColor = (GroundColor + CloudColor) * Light * 1.2;// + CityLightColor * 0.5;

	//gl_FragColor = GroundColor;
}