
uniform sampler2D TextureL0; //Ground
uniform sampler2D TextureL1; //Cloud
uniform sampler2D TextureL2; //CityLight
uniform float TimeMs;

varying vec4 DiffLight;
varying vec4 AmbiLight;
varying vec4 Light;

void main(void) 
{
	float t = TimeMs / 800000.0;
	vec4 Ground = texture2D( TextureL0, vec2(gl_TexCoord[0]) );
	vec4 Cloud = texture2D( TextureL1, vec2(gl_TexCoord[0]) + vec2(t,0) );
	vec4 CityLight = texture2D( TextureL2, vec2(gl_TexCoord[0]) + vec2( -0.03, 0 ), -1 );
	CityLight = vec4(CityLight.r) * vec4( 0.8, 0.8, 1, 0 );

	gl_FragColor = ( Ground + vec4(Cloud.r) ) * DiffLight * 2 + AmbiLight;
	gl_FragColor += CityLight * ( vec4(0.8) - Light );
	//gl_FragColor = CityLight;
}