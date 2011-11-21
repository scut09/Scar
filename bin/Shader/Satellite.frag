
uniform sampler2D TextureL0; //Ground
uniform sampler2D TextureL1; //CityLight
uniform sampler2D TextureL2; //Cloud
uniform float TimeMs;

varying vec4 DiffLight;
varying vec4 AmbiLight;
varying vec4 Light;

void main(void) 
{
	float t = TimeMs / 50000.0;
	vec4 GroundColor = texture2D( TextureL0, vec2(gl_TexCoord[0]) );
	vec4 CityLightColor = texture2D( TextureL1, vec2(gl_TexCoord[0]) );
	vec4 CloudColor = texture2D( TextureL2, vec2(gl_TexCoord[0]) + vec2(t,0) );

	//CloudColor = CloudColor * 0.4;
	CloudColor = vec4( (CloudColor.rbg * CloudColor.a), 1.0 );

	//gl_FragColor = (GroundColor + CloudColor) * Light * 1.2;// + CityLightColor * (1 - Light);
	gl_FragColor = (GroundColor) * Light * 1.2;
	//gl_FragColor = CloudColor;
}